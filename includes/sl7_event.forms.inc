<?php

/**
 * @file
 *  Форма и функции регистрации на мероприятие.
 */

/**
 * Форма заявки на мероприятие.
 *
 * @param $form
 * @param $form_state
 * @param null $event
 *  Или ID мероприятия или объект SL7Event. Если не указано, то берется
 *  текущий объект со страницы.
 * @return array|mixed
 */
function sl7_event_form($form, &$form_state, $event = NULL) {
  global $user;

  $sl7_event = &$form_state['sl7_event'];

  if (!isset($sl7_event['object'])) {
    if (!empty($event)) {
      $event = is_object($event) ? $event : sl7_event_load($event);
    }
    $sl7_event['object'] = ($event) ? $event : menu_get_object();
  }

  // Определение настроек формы по умолчанию.
  if (!isset($sl7_event['checkup'])) $sl7_event['checkup'] = TRUE;
  if (!isset($sl7_event['participant'])) $sl7_event['participant'] = FALSE;
  if (!isset($sl7_event['message'])) $sl7_event['message'] = NULL;
  if (!isset($sl7_event['message_button'])) $sl7_event['message_button'] = FALSE;
  if (!isset($sl7_event['message_button_text'])) $sl7_event['message_button_text'] = NULL;
  if (!isset($sl7_event['stage'])) $sl7_event['stage'] = 'profile';
  $event_wrapper = $sl7_event['object']->wrapper();

  // Проверка пользователя на участие в мероприятии.
  if ($sl7_event['checkup'] == TRUE) {
    $participants = $event_wrapper->sl7_event_participants->value();
    foreach ($participants as $participant) {
      if ($participant->uid == $user->uid) {
        $sl7_event['participant'] = TRUE;
        // Если мероприятие платное.
        if ($sl7_event['object']->free == 0) {
          $form_state['sl7_payment']['object'] = sl7_event_get_participant_order($sl7_event['object']->eid, $GLOBALS['user']->uid);
          // Если участвует, но нет оплаты.
          if ((is_object($form_state['sl7_payment']['object']) && $form_state['sl7_payment']['object']->state != 'paid') || $form_state['sl7_payment']['object'] == FALSE) {
            $sl7_event['checkup'] = FALSE;
            $sl7_event['message_button'] = TRUE;
            $sl7_event['message_button_text'] = 'Оплатить участие';
            $sl7_event['stage'] = 'message';
            $sl7_event['message'] = 'Вы являетесь участником этого мероприятия, но оплата ещё не произведена.';
          }
          // Участвует и есть оплата.
          else {
            $sl7_event['checkup'] = FALSE;
            $sl7_event['stage'] = 'message';
            $sl7_event['message'] = 'Вы являетесь участником этого мероприятия. Оплата произведена.';
          }
        }
        // Бесплатное мероприятие.
        else {
          $sl7_event['checkup'] = FALSE;
          $sl7_event['stage'] = 'message';
          $sl7_event['message'] = 'Вы являетесь участником этого мероприятия.';
        }
      }
    }
  }

  // Если аноним, то на форму входа/логина.
  if ($user->uid == 0) {
    $sl7_event['stage'] = 'login';
  }

  // Проверка даты мероприятия.
  $date_start_stamp = new DateTime($sl7_event['object']->sl7_event_date['und'][0]['value'], new DateTimeZone($sl7_event['object']->sl7_event_date['und'][0]['timezone_db']));
  $date_start = $date_start_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()))->format('U');
  $date_end_stamp = new DateTime($sl7_event['object']->sl7_event_date['und'][0]['value2'], new DateTimeZone($sl7_event['object']->sl7_event_date['und'][0]['timezone_db']));
  $date_end = $date_end_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()))->format('U');
  $date_now = time();

  if ($date_now >= $date_start && $date_now >= $date_end) {
    $sl7_event['message'] = 'Мероприятие уже закончилось.';
    $sl7_event['stage'] = 'message';
    $sl7_event['message_button'] = FALSE;
  }

  if ($sl7_event['checkup'] == TRUE) {
    // Уже началось, но ещё не закончилось.
    if ($date_now >= $date_start && $date_now < $date_end) {
      $sl7_event['message'] = 'Мероприятие уже началось.';
      $sl7_event['stage'] = 'message';
      $sl7_event['checkup'] = FALSE;
      $sl7_event['message_button'] = TRUE;
      $sl7_event['message_button_text'] = 'Всё равно продолжить регистрацию';
    }
  }

  // Проверка (обязательная) на свободные места на мероприятии.
  if ($sl7_event['participant'] == FALSE) {
    $available = sl7_event_get_remaining_seats($sl7_event['object']);
    if ($sl7_event['object']->seats != 0 && $available == 0) {
      $sl7_event['stage'] = 'message';
      $sl7_event['message'] = 'Свободных мест на мероприятии нет.';
      $sl7_event['message_button'] = FALSE;
    }
  }

  $form['#prefix'] = '<div id="sl7-event-participant-form">';
  $form['#suffix'] = '</div>';
  $form['actions'] = array('#type' => 'actions');
  $form['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'sl7_event') . '/css/sl7_event.form.css',
    ),
  );

  switch($sl7_event['stage']) {
    case 'login':
      return sl7_event_login_form($form, $form_state);
      break;

    case 'profile':
      return sl7_event_profile2_form($form, $form_state);
      break;

    case 'payment':
      return sl7_payment_form($form, $form_state);
      break;

    case 'message':
      return sl7_event_message_form($form, $form_state);
      break;
  }
}

/**
 * Форма регистрации/входа на сайт.
 */
function sl7_event_login_form($form, &$form_state) {

  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => 'E-mail',
    '#required' => TRUE,
  );

  $form['pass'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#required' => TRUE,
  );

  $form['actions']['login'] = array(
    '#type' => 'submit',
    '#value' => 'Войти',
    '#submit' => array('sl7_event_login_form_login_submit'),
    '#validate' => array('sl7_event_login_form_mail_validate'),
    '#attributes' => array(
      'class' => array('button', 'btn'),
    ),
    '#ajax' => array(
      "callback" => "sl7_event_form_ajax_submit",
      "wrapper" => "sl7-event-participant-form",
      "effect" => "fade",
      'method' => 'replace',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['actions']['registration'] = array(
    '#type' => 'submit',
    '#value' => 'Зарегистрироваться',
    '#submit' => array('sl7_event_login_form_registration_submit'),
    '#validate' => array('sl7_event_login_form_mail_validate'),
    '#attributes' => array(
      'class' => array('button', 'btn'),
    ),
    '#ajax' => array(
      "callback" => "sl7_event_form_ajax_submit",
      "wrapper" => "sl7-event-participant-form",
      "effect" => "fade",
      'method' => 'replace',
      'progress' => array('type' => 'none'),
    ),
  );

  return $form;
}

/**
 * Форма с полями от profile2.
 */
function sl7_event_profile2_form($form, &$form_state, $user = NULL) {
  if (empty($user)) global $user;

  module_load_include('inc', 'profile2_page', 'profile2_page');

  $wrapper = $form_state['sl7_event']['object']->wrapper();
  $profile_type_id = $wrapper->sl7_event_profile->raw();
  $form_state['sl7_event']['profile_type'] = db_select('profile_type', 'pt')
    ->condition('pt.id', $profile_type_id)
    ->fields('pt', array('type'))
    ->execute()
    ->fetchField();

  $profile2 = profile2_by_uid_load($user->uid, $form_state['sl7_event']['profile_type']);
  $form = entity_ui_get_form('profile2', $profile2, 'edit');

  if (empty($form_state['profiles'])) {
    $profile = profile2_load_by_user($user->uid, $form_state['sl7_event']['profile_type']);
    if (empty($profile)) {
      $profile = profile2_create(array('type' => $form_state['sl7_event']['profile_type'], 'uid' => $user->uid));
    }
    $form_state['profiles'][$profile->type] = $profile;
    profile2_attach_form($form, $form_state);
  }

  $form['#token'] = FALSE;
  $form['#prefix'] = '<div id="sl7-event-participant-form">';
  $form['#suffix'] = '</div>';

  unset($form['actions']['submit']);
  $form['actions']['submit'] = array('#type' => 'submit');
  if (module_exists('sl7_payment')) {
    $form['actions']['submit']['#value'] = $form_state['sl7_event']['object']->free == 1 ? 'Принять участие' : 'Оплатить участие';
  }
  else {
    $form['actions']['submit']['#value'] = 'Принять участие';
  }
  $form['actions']['submit']['#ajax'] = array(
    "callback" => "sl7_event_form_ajax_submit",
    "wrapper" => "sl7-event-participant-form",
    "effect" => "slide",
    'method' => 'replace',
    'progress' => array('type' => 'none'),
  );

  $form['#submit'] = array('sl7_event_form_submit');
  $form['#validate'] = array('sl7_event_profile2_form_validate');

  drupal_set_title($form_state['sl7_event']['object']->label);

  return $form;
}

/**
 * Форма-сообщение.
 */
function sl7_event_message_form($form, &$form_state) {
  $form['#token'] = FALSE;

  $form['message_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('sl7-event-participant-form-message'),
    ),
  );

  $form['message_container']['message'] = array(
    '#markup' => '<p>' . $form_state['sl7_event']['message'] . '</p>',
  );

  if ($form_state['sl7_event']['message_button'] == TRUE) {
    $form['message_container']['actions'] = array('#type' => 'actions');
    $form['message_container']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => !empty($form_state['sl7_event']['message_button_text']) ? $form_state['sl7_event']['message_button_text'] : 'Продолжить',
      '#attributes' => array(
        'class' => array('button', 'btn'),
      ),
      '#ajax' => array(
        "callback" => "sl7_event_form_ajax_submit",
        "wrapper" => "sl7-event-participant-form",
        "effect" => "slide",
        'method' => 'replace',
        'progress' => array('type' => 'none'),
      ),
    );
  }

  return $form;
}

function sl7_event_login_form_mail_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['mail'])) {
    form_set_error('mail', 'Неверный формат e-mail адреса.');
  }
}

function sl7_event_profile2_form_validate($form, &$form_state) {
  foreach ($form_state['input']['profile_' . $form_state['sl7_event']['profile_type']] as $field => $values) {
    if (empty($values['und'][0]['value'])
      && isset($form['profile_' . $form_state['sl7_event']['profile_type']][$field]['und'][0]['#required'])
      && $form['profile_' . $form_state['sl7_event']['profile_type']][$field]['und'][0]['#required'] == TRUE) {
      form_set_error('profile_' . $form_state['sl7_event']['profile_type'] . '][' . $field, t('!name field is required.', array('!name' => $form['profile_' . $form_state['sl7_event']['profile_type']][$field]['und'][0]['#title'])));
    }
  }
}

function sl7_event_form_ajax_submit($form, &$form_state) {
  return $form;
}

function sl7_event_form_submit($form, &$form_state) {
  $sl7_event = &$form_state['sl7_event'];

  switch($sl7_event['stage']) {
    case 'login':
      $sl7_event['stage'] = 'profile';
      break;

    case 'profile';
      global $user;

      // Подготовка profile2 и сохранение.
      $profile_fields = $form_state['input']['profile_' . $sl7_event['profile_type']];
      foreach ($profile_fields as $field_name => $field_value) {
        if (isset($form_state['profiles'][$sl7_event['profile_type']]->{$field_name})) {
          $form_state['profiles'][$sl7_event['profile_type']]->{$field_name} = $field_value;
        }
      }
      profile2_form_submit_cleanup($form, $form_state);
      profile2_save($form_state['profiles'][$sl7_event['profile_type']]);

      // Если мероприятие платное, то на страницу оплаты.
      if ($sl7_event['object']->free == 0) {
        sl7_event_form_prepare_payment($form, $form_state, $profile_fields);
        $sl7_event['stage'] = 'payment';
        $sl7_event['checkup'] = FALSE;
      }
      // Если бесплатное, то пишем, что регистрация успешна.
      else {
        drupal_set_message('Вы успешно зарегистрированы на мероприятие.', 'status');
        $sl7_event['stage'] = 'message';
        $sl7_event['checkup'] = FALSE;
        $sl7_event['message_button'] = FALSE;
        $sl7_event['message'] = 'Вы успешно зарегистрированы на мероприятие.';
      }

      // Грузим участников мероприятия.
      $event_wrapper = $sl7_event['object']->wrapper();
      $participants = $event_wrapper->sl7_event_participants->value();

      // Проверяем, есть ли участник в списке.
      $participant_uid = '';
      foreach($participants as $p_uid => $p_values) {
        if ($p_uid == $user->uid) {
          $sl7_event['participant'] = TRUE;
          $participant_uid = $p_uid;
        }
      }

      // Если нету, добавляем его.
      if (!$sl7_event['participant']) {
        $event_wrapper->sl7_event_participants[] = $user->uid;
        $event_wrapper->save();
        $sl7_event['participant'] = TRUE;
        // Вызываем rules: оповещения участника.
        rules_invoke_event('sl7_event_after_participate', $user, $sl7_event['object']);
      }
      break;

    case 'message':
      // Не обращать внимание на начало мероприятия.
      $sl7_event['checkup'] = FALSE;
      // Показать кнопку продолжения действий.
      $sl7_event['message_button'] = TRUE;
      $sl7_event['stage'] = 'profile';
      break;
  }

  if (isset($form_state['storage']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['storage']['form_build_id'];
  }
  $form_state['storage']['form_build_id'] = $form_state['values']['form_build_id'];

  $form_state['rebuild'] = TRUE;
}

/**
 * Вход пользователя на сайт.
 */
function sl7_event_login_form_login_submit($form, &$form_state) {
  if (SL7ApiUser::loginByMail($form_state['values']['mail'], $form_state['values']['pass'])) {
    sl7_event_form_submit($form, $form_state);
  }
  else {
    drupal_set_message('Неправильный логин или пароль.', 'error');
  }
}

/**
 * Регистрация пользователя на сайте.
 */
function sl7_event_login_form_registration_submit($form, &$form_state) {
  if (SL7ApiUser::regByMail($form_state['values']['mail'], $form_state['values']['pass'])) {
    sl7_event_form_submit($form, $form_state);
  }
  else {
    drupal_set_message('Что-то пошло не так. Повторите попытку.', 'error');
  }
}

/**
 * Подготовка данных для платежа.
 *
 * @param $form
 * @param $form_state
 * @param array $customer
 *  Массив с полями для custom платежа.
 * @param null $account
 */
function sl7_event_form_prepare_payment($form, &$form_state, array $customer, $account = NULL) {
  if (empty($account)) {
    global $user;
    $uid = $user->uid;
  }
  else {
    $uid = is_object($account) ? $account->uid : $account;
  }

  // Подготовка customer полей.
  $form_state['sl7_payment']['customer'] = $customer;

  // Подготовка платежа.
  $form_state['sl7_payment']['values']['recipient'] = $uid;
  $form_state['sl7_payment']['values']['data'] = array(
    'destination' => 'sl7_event',
    'eid' => $form_state['sl7_event']['object']->eid,
    'participant' => $uid,
  );
  $form_state['sl7_payment']['values']['item'][] = array(
    'label' => 'Оплата участия в мероприятии: ' . check_plain($form_state['sl7_event']['object']->label),
    'quantity' => 1,
    'amount' => $form_state['sl7_event']['object']->amount,
  );
}