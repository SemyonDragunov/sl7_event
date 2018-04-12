<?php

/**
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

/**
 * UI controller for sl7_event.
 */
class SL7EventUIController extends EntityDefaultUIController {

  public function hook_menu() {

    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%sl7_event';

    $items[$this->path . '/view'] = array(
      'title'  => 'Просмотр списка мероприятий',
      'type'   => MENU_DEFAULT_LOCAL_TASK,
      'context'=> MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight' => -10,
    );

    $items[$this->path . '/add'] = array(
      'title'            => 'Создать мероприятие',
      'page callback'    => 'sl7_event_get_edit_form',
      'page arguments'   => array('create', NULL),
      'access callback'  => 'sl7_event_access',
      'access arguments' => array('create'),
      'type'             => MENU_LOCAL_TASK,
      'weight'           => -9,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/' . $wildcard] = array(
      'title callback'   => 'sl7_event_label',
      'title arguments'  => array($id_count),
      'page callback'    => 'entity_ui_entity_page_view',
      'page arguments'   => array($id_count),
      'access callback'  => 'sl7_event_access',
      'access arguments' => array('participation', $id_count),
      'load arguments'   => array($this->entityType),
      'type' => MENU_CALLBACK,
    );

    $items[$this->path . '/' . $wildcard . '/view'] = array(
      'title'  => t('View'),
      'type'   => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    $items[$this->path . '/' . $wildcard . '/edit'] = array(
      'title'            => t('Edit'),
      'page callback'    => 'sl7_event_get_edit_form',
      'page arguments'   => array('edit', $id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_event_access',
      'access arguments' => array('manage'),
      'type'             => MENU_LOCAL_TASK,
      'weight'           => -9,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$this->path . '/' . $wildcard . '/delete'] = array(
      'title'            => t('Delete'),
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array('sl7_event_delete_form', $id_count),
      'load arguments'   => array($this->entityType),
      'access callback'  => 'sl7_event_access',
      'access arguments' => array('delete'),
      'type'             => MENU_LOCAL_TASK,
      'context'          => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'weight'           => -7,
    );

    $module_path = drupal_get_path('module', $this->entityInfo['module']);
    foreach ($items as &$item) {
      $item['file'] = 'includes/sl7_event.ui.inc';
      $item['file path'] = $module_path;
    }
    unset($item);

    return $items;
  }

  public function form($form, &$form_state) {

    $event = $form_state['sl7_event'];

    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => 'Название мероприятия',
      '#default_value' => !empty($event->label) ? $event->label : '',
      '#maxlength' => 128,
      '#required' => TRUE,
    );

    $form['seats'] = array(
      '#type' => 'textfield',
      '#title' => 'Количество мест',
      '#description' => 'Если установить <b>0</b>, то количество мест будет неограниченно.',
      '#default_value' => !empty($event->seats) ? $event->seats : 0,
      '#maxlength' => 8,
      '#required' => TRUE,
    );

    if (module_exists('sl7_payment')) {
      $form['payment'] = array (
        '#type' => 'fieldset',
        '#title' => 'Оплата',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#weight' => 5,
      );
      $form['payment']['free'] = array(
        '#type'          => 'radios',
        '#title'         => 'Платное участие?',
        '#default_value' => isset($event->free) ? $event->free : 1,
        '#options'       => array(
          1 => 'Бесплатное',
          0 => 'Платное',
        ),
        '#required'      => TRUE,
      );
      $form['payment']['amount'] = array(
        '#type' => 'textfield',
        '#title' => 'Стоимость участия',
        '#default_value' => !empty($event->amount) ? $event->amount : 0,
        '#element_validate' => array('element_validate_number'),
        '#required'      => TRUE,
        '#states' => array(
          'visible' => array(
            ':input[name="free"]' => array(
              'value' => 0,
            ),
          ),
        ),
      );
    }
    else {
      $form['free'] = array(
        '#type' => 'hidden',
        '#value' => 1,
      );
    }

    field_attach_form('sl7_event', $event, $form, $form_state);

    // Убираем из вывода поле "Участники".
    $form['sl7_event_participants']['#access'] = FALSE;

    $form['#after_build'][] = '_sl7_event_edit_form_required_after_build';

    $form['actions'] = array(
      '#type' => 'actions',
    );
    $form['actions']['submit'] = array(
      '#type'   => 'submit',
      '#value'  => !empty($event->eid) ? 'Сохранить' : 'Создать',
      '#weight' => 0,
    );
    $form['actions']['delete'] = array(
      '#markup' => !empty($event->eid) ? l(t('Delete'), SL7_EVENT_PATH . '/' . $event->eid . '/delete', array('attributes' => array('class' => array('button remove')), 'query' => array('destination' => SL7_EVENT_ADMIN_PATH . '/manage'))) : '',
    );

    return $form;
  }

  public function formValidate($form, &$form_state) {
    if (module_exists('sl7_payment')) {
      if ($form_state['values']['free'] == FALSE && $form_state['values']['amount'] <= 0) {
        form_set_error('amount', 'Нельзя указывать платное мероприятие и нулевую стоимость участия.');
      }
    }
  }

  public function formSubmit($form, &$form_state) {
    $event = $this->entityFormSubmitBuildEntity($form, $form_state);
    $event->save();
    $label = check_plain($event->label);

    $form_state['redirect'] = $event->realPath();

    if (!empty($event->is_new)) {
      drupal_set_message("Мероприятие \"$label\" создано.");
    }
    else {
      drupal_set_message("Мероприятие \"$label\" сохранено.");
    }
  }

  public function deleteForm($form, &$form_state) {
    $event = $form_state['sl7_event'];
    $label = check_plain($event->label);

    $form = confirm_form($form,
      "Вы уверены в удалении мероприятия \"$label\"?",
      $event->realPath(),
      '<p>' . 'Удаление не может быть отменено.' . '</p>',
      t('Delete'),
      t('Cancel'),
      'confirm'
    );

    return $form;
  }

  public function deleteFormSubmit($form, &$form_state) {
    $event = $form_state['sl7_event'];
    $label = check_plain($event->label);

    sl7_event_delete($event);

    drupal_set_message("Мероприятие \"$label\" удалено.");

    $form_state['redirect'] = SL7_EVENT_ADMIN_PATH . '/manage';
  }
}

function sl7_event_edit_form($form, &$form_state) {
  return entity_ui_controller($form_state['entity_type'])->form($form, $form_state);
}

/**
 * Убираем поле "Цена" (обязательность), если мероприятие бесплатное.
 */
function _sl7_event_edit_form_required_after_build(&$form, $form_state) {
  if ($form_state['process_input']) {
    if ($form_state['values']['free'] == 1) {
      unset($form['amount']);
    }
  }

  return $form;
}

function sl7_event_edit_form_validate($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->formValidate($form, $form_state);
}

function sl7_event_edit_form_submit($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->formSubmit($form, $form_state);
}

function sl7_event_delete_form($form, &$form_state, $event) {
  $entity_type = 'sl7_event';
  $form_state['entity_type'] = $entity_type;
  $form_state[$entity_type] = $event;
  return entity_ui_controller($form_state['entity_type'])->deleteForm($form, $form_state);
}

function sl7_event_delete_form_submit($form, &$form_state) {
  entity_ui_controller($form_state['entity_type'])->deleteFormSubmit($form, $form_state);
}

function sl7_event_get_edit_form($op = 'create', $event = NULL) {
  $form_state = array(
    'entity_type' => 'sl7_event',
    'op' => $op,
  );

  switch ($op) {
    case 'create':
      drupal_set_title('Создать мероприятие');
      $form_state['sl7_event'] = sl7_event_create();
      break;
    case 'edit':
      $form_state['sl7_event'] = is_object($event) ? $event : sl7_event_load($event);
      drupal_set_title('Редактирование ' . $form_state['sl7_event']->label);
      break;
    default:
      $form_state['sl7_event'] = $event;
      break;
  }

  form_load_include($form_state, 'inc', 'sl7_event', 'includes/sl7_event.ui');

  $form_state['build_info']['args'] = array($op, $event);

  return drupal_build_form('sl7_event_edit_form', $form_state);
}