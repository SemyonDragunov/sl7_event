<?php

/**
 * Class sl7_event entities.
 */
class SL7Event extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'sl7_event');
  }

  protected function defaultLabel() {
    return $this->label;
  }

  protected function defaultUri() {
    return array('path' => $this->realPath());
  }

  public function realPath() {
    return SL7_EVENT_PATH . '/' . $this->identifier();
  }
}

/**
 * The Controller for sl7_event entities.
 */
class SL7EventController extends EntityAPIController {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  public function create(array $values = array()) {
    global $user;

    $values += array(
      'eid' => '',
      'is_new' => TRUE,
      'label' => '',
      'free' => '',
      'seats' => 0,
      'amount' => 0,
      'uid' => $user->uid,
      'created' => REQUEST_TIME,
      'changed' => REQUEST_TIME,
    );

    return parent::create($values);
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);

    field_attach_prepare_view('sl7_event', array($entity->eid => $entity), $view_mode, $langcode);
    entity_prepare_view('sl7_event', array($entity->eid => $entity), $langcode);
    $content += field_attach_view('sl7_event', $entity, $view_mode, $langcode);

    // Убираем из вывода поля "Участники" и "Профиль".
    unset($content['sl7_event_profile']);
    unset($content['sl7_event_participants']);

    if ($view_mode == 'full') {
      // Js для карты.
      drupal_add_js(drupal_get_path('module', 'sl7_event') . '/js/sl7_event.ymaps.js');
      $setting = array('sl7_event' => array(
        'eventLabel' => $entity->label,
        'extraAddress' => !empty($entity->sl7_event_extra_address['und'][0]['value']) ? check_plain($entity->sl7_event_extra_address['und'][0]['value']) : NULL
      ));
      $content['#attached']['js'][] = array(
        'data' => $setting,
        'type' => 'setting'
      );

      // Поле-форма.
      $extra_fields = field_extra_fields_get_display('sl7_event', 'sl7_event', $view_mode);
      if (isset($extra_fields['form']) && $extra_fields['form']['visible']) {
        $content['form'] = array(
          '#markup' => SL7ApiForm::getRenderForm('sl7_event_form', $entity),
          '#weight' => $extra_fields['form']['weight'],
        );
      }
    }

    if ($view_mode == 'teaser') {
      // Fix. Убирем карту и форму регистрации в анонсе.
      unset($content['sl7_event_map']);
      unset($content['form']);

      $content['#contextual_links']['sl7_event'] = array(SL7_EVENT_PATH, array($entity->eid));
    }

    $content += array(
      '#theme'     => 'sl7_event__' . $view_mode,
      '#element'   => $entity,
      '#view_mode' => $view_mode,
      '#langcode'  => $langcode,
    );

    return $content;
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (empty($entity->is_new)) $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }
}

/**
 * Class SL7Order metadata controller.
 */
class SL7EventMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();

    $properties = &$info[$this->type]['properties'];

    $properties['label']['label'] = 'Название мероприятия';

    $properties['uid'] = array(
      'label' => 'Создатель',
      'description' => 'Имя пользователя создателя платежа.',
      'type' => 'user',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['seats'] = array(
      'label' => 'Мест осталось',
      'description' => 'Количество оставшихся мест на мероприятии.',
      'type' => 'integer',
      'getter callback' => 'sl7_event_metadata_seats',
      'computed' => TRUE,
      'entity views field' => TRUE,
    );

    $properties['free']['label'] = 'Бесплатно';
    $properties['free']['description'] = 'Бесплатное ли участие в мероприятии.';

    $properties['amount']['label'] = 'Стоимость участия';
    $properties['amount']['description'] = 'Стоимость участия в мероприятии.';
    $properties['amount']['getter callback'] = 'sl7_event_metadata_amount';

    $properties['created']['type'] = 'date';
    $properties['created']['label'] = 'Дата создания';
    $properties['created']['description'] = 'Время создания платежа.';

    $properties['changed']['type'] = 'date';
    $properties['changed']['label'] = 'Последние изменение';
    $properties['changed']['description'] = 'Дата и время последнего изменения платежа.';

    return $info;
  }
}

class SL7EventExtraFieldsController extends EntityDefaultExtraFieldsController {

  public function fieldExtraFields() {
    $extra_fields = array();

    $extra_fields['sl7_event']['sl7_event'] = array(
      'form' => array(
        'label' => array(
          'label' => 'Название',
          'description' => 'Название мероприятия.',
          'weight' => -10,
        ),
        'free' => array(
          'label' => 'Бесплатно',
          'description' => 'Платное участие?',
          'weight' => 7,
        ),
        'seats' => array(
          'label' => 'Мест осталось',
          'description' => 'Количество оставшихся мест на мероприятии.',
          'weight' => 6,
        ),
        'amount' => array(
          'label' => 'Стоимость участия',
          'description' => 'Стоимость участия в мероприятии.',
          'weight' => 8,
        ),
      ),
      'display' => array(
        'seats' => array(
          'label' => 'Мест осталось',
          'description' => 'Количество оставшихся мест на мероприятии.',
          'weight' => 4,
        ),
        'amount' => array(
          'label' => 'Стоимость участия',
          'description' => 'Стоимость участия в мероприятии.',
          'weight' => 5,
        ),
        'form' => array(
          'label' => 'Форма регистрации',
          'description' => 'Форма регистрации на мероприятие.',
          'weight' => 30,
        ),
      ),
    );

    return $extra_fields;
  }
}

/**
 * Views controller for sl7_event entities.
 */
class SL7EventViewsController extends EntityDefaultViewsController {

  public function views_data() {
    $data = parent::views_data();

    $data['sl7_event']['check_paying'] = array(
      'field' => array(
        'title' => 'Проверка оплаты',
        'help' => 'Показывает произведена или нет оплата.',
        'handler' => 'sl7_event_handler_sl7_event_check_paying',
      ),
    );
    $data['sl7_event']['reg_participant'] = array(
      'field' => array(
        'title' => 'Регистрация участника',
        'help' => 'Указывает прибыл ли участник на мероприятие.',
        'handler' => 'sl7_event_handler_sl7_event_reg_participant',
      ),
    );
    $data['sl7_event']['operations'] = array(
      'field' => array(
        'title' => 'Действия',
        'help' => 'Показывает все возможные операции.',
        'handler' => 'sl7_event_handler_operations',
      ),
    );

    return $data;
  }
}