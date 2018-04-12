<?php

function template_preprocess_flag__sl7_event_reg_participant(&$variables) {
  global $user;
  $initialized = &drupal_static(__FUNCTION__, array());

  // Some typing shotcuts:
  $flag =& $variables['flag'];
  $action = $variables['action'];
  $entity_id = $variables['entity_id'];
  $uid = $variables['uid'];
  $errors = implode('<br />', $variables['errors']);
  $flag_name_css = str_replace('_', '-', $flag->name);

  // Generate the link URL.
  $link_type = $flag->get_link_type();
  $link = array(
    'href' => "ajax/sl7_event/flag/$action/$flag->name/$entity_id/$uid",
    'query' => drupal_get_destination(),
  );
  if (isset($link['title']) && empty($link['html'])) {
    $link['title'] = check_plain($link['title']);
  }

  // Replace the link with the access denied text if unable to flag.
  if ($action == 'unflag' && !$flag->access($entity_id, 'unflag')) {
    $link['title'] = $flag->get_label('unflag_denied_text', $entity_id);
    unset($link['href']);
  }

  // Anonymous users always need the JavaScript to maintain their flag state.
  if ($user->uid == 0) {
    $link_type['uses standard js'] = TRUE;
  }

  // Load the JavaScript/CSS, if the link type requires it.
  if (!isset($initialized[$link_type['name']])) {
    if ($link_type['uses standard css']) {
      drupal_add_css(drupal_get_path('module', 'flag') . '/theme/flag.css');
    }
    if ($link_type['uses standard js']) {
      drupal_add_js(drupal_get_path('module', 'flag') . '/theme/flag.js');
    }
    $initialized[$link_type['name']] = TRUE;
  }

  $variables['link'] = $link;
  $variables['link_href'] = isset($link['href']) ? check_url(url($link['href'], $link)) : FALSE;
  $variables['link_text'] = isset($link['title']) ? $link['title'] : $flag->get_label($action . '_short', $entity_id);
  $variables['link_title'] = isset($link['attributes']['title']) ? check_plain($link['attributes']['title']) : check_plain(strip_tags($flag->get_label($action . '_long', $entity_id)));
  $variables['status'] = ($action == 'flag' ? 'unflagged' : 'flagged');
  $variables['flag_name_css'] = $flag_name_css;

  $variables['flag_wrapper_classes_array'] = array();
  $variables['flag_wrapper_classes_array'][] = 'flag-wrapper';
  $variables['flag_wrapper_classes_array'][] = 'flag-' . $flag_name_css;
  $variables['flag_wrapper_classes_array'][] = 'flag-' . $flag_name_css . '-' . $entity_id;

  $variables['flag_classes_array'] = array();
  $variables['flag_classes_array'][] = 'flag';
  if (isset($link['href'])) {
    $variables['flag_classes_array'][] = $variables['action'] . '-action';
    $variables['flag_classes_array'][] = 'flag-link-' . $flag->link_type;
  }
  else {
    $variables['flag_classes_array'][] = $variables['action'] . '-disabled';
  }
  if (isset($link['attributes']['class'])) {
    $link['attributes']['class'] = is_string($link['attributes']['class']) ? array_filter(explode(' ', $link['attributes']['class'])) : $link['attributes']['class'];
    $variables['flag_classes_array'] = array_merge($variables['flag_classes_array'], $link['attributes']['class']);
  }
  $variables['message_classes_array'] = array();
  if ($variables['after_flagging']) {
    $variables['message_classes_array'][] = 'flag-message';
    if ($errors) {
      $variables['message_classes_array'][] = 'flag-failure-message';
      $variables['message_text'] = $errors;
    }
    else {
      $inverse_action = ($action == 'flag' ? 'unflag' : 'flag');
      $variables['message_classes_array'][] = 'flag-success-message';
      $variables['message_classes_array'][] = 'flag-' . $variables['status'] . '-message';
      $variables['message_text'] = $flag->get_label($inverse_action . '_message', $entity_id);
      $variables['flag_classes_array'][] = $variables['status'];
      // By default we make our JS code remove, after a few seconds, only
      // success messages.
      $variables['message_classes_array'][] = 'flag-auto-remove';
    }
  }
  else {
    $variables['message_text'] = '';
  }

  $variables['flag_wrapper_classes'] = implode(' ', $variables['flag_wrapper_classes_array']);
  $variables['flag_classes'] = implode(' ', $variables['flag_classes_array']);
  $variables['message_classes'] = implode(' ', $variables['message_classes_array']);
}

function template_preprocess_sl7_event__teaser(&$variables) {
  $entity = sl7_event_load($variables['element']->eid);
  $element = entity_view('sl7_event', array($entity), 'teaser');
  $element = $element['sl7_event'][$variables['element']->eid];
  $event_wrapper = $entity->wrapper();

  $variables['title_suffix'] = array(
    'contextual_links' => array(
      '#type' => 'contextual_links',
      '#contextual_links' => $element['#contextual_links'],
      '#element' => $element,
    ),
  );

  $date_start_stamp = new DateObject($entity->sl7_event_date['und'][0]['value'], $entity->sl7_event_date['und'][0]['timezone_db']);
  $date_start_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()));
  $variables['date_start'] = $date_start_stamp->format(SL7_DATE_FORMAT_WEEKDAY_HOUR);
  $date_start = $date_start_stamp->format('U');
  $date_end_stamp = new DateTime($entity->sl7_event_date['und'][0]['value2'], new DateTimeZone($entity->sl7_event_date['und'][0]['timezone_db']));
  $date_end = $date_end_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()))->format('U');
  $date_now = time();

  // Нет свободных мест
  $available = sl7_event_get_remaining_seats($entity);
  if ($entity->seats != 0 && $available == 0) {
    $variables['event_state'] = 'no_seats';
  }

  $variables['element']->seats = $available;

  // Мероприятие закончилось
  if ($date_now >= $date_start && $date_now >= $date_end) {
    $variables['event_state'] = 'end';
  }
  // Уже началось, но ещё не закончилось
  elseif ($date_now >= $date_start && $date_now < $date_end) {
    $variables['event_state'] = 'start';
  }

  if (!empty($entity->sl7_event_category)) {
    $variables['category'] = '';
    $total = count($entity->sl7_event_category['und']);
    $counter = 0;
    foreach ($entity->sl7_event_category['und'] as $category) {
      $counter++;
      if ($counter == $total) {
        $variables['category'] .= l($category['taxonomy_term']->name, '/taxonomy/term/' . $category['taxonomy_term']->tid);
      }
      else {
        $variables['category'] .= l($category['taxonomy_term']->name, '/taxonomy/term/' . $category['taxonomy_term']->tid) . ', ';
      }
    }
  }

  $variables['classes_array'][] = 'sl7-event';
  $variables['classes_array'][] = 'teaser';
  $variables['classes_array'][] = 'contextual-links-region';

  drupal_add_css(drupal_get_path('module', 'sl7_event') . '/css/sl7_event.css');
}

function template_preprocess_sl7_event__full(&$variables) {
  $entity = sl7_event_load($variables['element']->eid);
  $element = entity_view('sl7_event', array($entity), 'full');
  $element = $element['sl7_event'][$variables['element']->eid];
  $event_wrapper = $entity->wrapper();

  // Поля
  $info_sl7_event_body = field_info_instance('sl7_event', 'sl7_event_body', 'sl7_event');
  $variables['body'] = field_view_field('sl7_event', $entity, 'sl7_event_body', $info_sl7_event_body['display']['default']);

  $info_sl7_event_map = field_info_instance('sl7_event', 'sl7_event_map', 'sl7_event');
  $variables['map'] = field_view_field('sl7_event', $entity, 'sl7_event_map', $info_sl7_event_map['display']['default']);

  $info_sl7_event_date = field_info_instance('sl7_event', 'sl7_event_date', 'sl7_event');
  $variables['date'] = field_view_field('sl7_event', $entity, 'sl7_event_date', $info_sl7_event_date['display']['default']);

  $info_sl7_event_category = field_info_instance('sl7_event', 'sl7_event_category', 'sl7_event');
  $variables['category'] = field_view_field('sl7_event', $entity, 'sl7_event_category', $info_sl7_event_category['display']['default']);

  $variables['seats'] = $element['seats'];
  $variables['amount'] = $element['amount'];
  $variables['form'] = $element['form'];

  $date_start_stamp = new DateObject($entity->sl7_event_date['und'][0]['value'], $entity->sl7_event_date['und'][0]['timezone_db']);
  $date_start_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()));
  $date_start = $date_start_stamp->format('U');
  $date_end_stamp = new DateTime($entity->sl7_event_date['und'][0]['value2'], new DateTimeZone($entity->sl7_event_date['und'][0]['timezone_db']));
  $date_end = $date_end_stamp->setTimeZone(new DateTimeZone(drupal_get_user_timezone()))->format('U');
  $date_now = time();

  // Нет свободных мест
  $available = sl7_event_get_remaining_seats($entity);
  if ($entity->seats != 0 && $available == 0) {
    $variables['event_state'] = 'no_seats';
  }

  // Мероприятие закончилось
  if ($date_now >= $date_start && $date_now >= $date_end) {
    $variables['event_state'] = 'end';
  }
  // Уже началось, но ещё не закончилось
  elseif ($date_now >= $date_start && $date_now < $date_end) {
    $variables['event_state'] = 'start';
  }

  $variables['classes_array'][] = 'sl7-event';
  $variables['classes_array'][] = 'full';
  $variables['classes_array'][] = 'contextual-links-region';

  drupal_add_css(drupal_get_path('module', 'sl7_event') . '/css/sl7_event.css');
}