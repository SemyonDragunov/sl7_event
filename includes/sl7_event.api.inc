<?php

/**
 * @file
 * Api for sl7_event entities.
 * 
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

function sl7_event_create($values = array()) {
  return entity_get_controller('sl7_event')->create($values);
}

function sl7_event_load($event_ids, $reset = FALSE) {
  $order = sl7_event_load_multiple(array($event_ids), array(), $reset);
  return reset($order);
}

function sl7_event_load_multiple($event_ids = array(), $conditions = array(), $reset = FALSE) {
  $event_ids = ($event_ids) ? $event_ids : FALSE;
  return entity_load('sl7_event', $event_ids, $conditions, $reset);
}

function sl7_event_delete(SL7Event $event) {
  $event->delete();
}

function sl7_event_delete_multiple(array $eids) {
  entity_get_controller('sl7_event')->delete($eids);
}

function sl7_event_save(SL7Event $event) {
  return entity_save('sl7_event', $event);
}

function sl7_event_uri(SL7Event $event){
  return array(
    'path' => $event->realPath(),
  );
}

function sl7_event_label(SL7Event $event) {
  return $event->label;
}

/**
 * Возвращает платёж существующего участника.
 *
 * @param $participant_uid
 *  UID участника.
 * @param $eid
 *  Event ID (eid) or object SL7Event.
 * @return SL7Order
 */
function sl7_event_get_participant_order($eid, $participant_uid) {
  $eid = is_object($eid) ? $eid->eid : $eid;

  $oids = db_select('sl7_order', 'o')
    ->condition('o.recipient', $participant_uid)
    ->fields('o', array('oid'))
    ->execute()
    ->fetchCol();

  if (!empty($oids)) {
    $orders = sl7_order_load_multiple($oids);

    foreach($orders as $order) {
      if ($order->data['destination'] == 'sl7_event' && $order->data['eid'] == $eid) {
        return $order;
      }
    }
  }

  return FALSE;
}

/**
 * Сколько осталось мест на мероприятии.
 * @param $event
 *  Event ID (eid) or object SL7Event.
 * @return integer
 */
function sl7_event_get_remaining_seats($event) {
  $event = is_object($event) ? $event : sl7_event_load($event);

  if ($event->seats == 0) {
    return 0;
  }

  $wrapper = $event->wrapper();
  $participants = $wrapper->sl7_event_participants->value();

  // Если мероприятие платное, убираем не оплативших.
  if ($event->free == 0) {
    foreach ($participants as $key => $people) {
      $order = sl7_event_get_participant_order($event->eid, $people->uid);

      if ($order->enroll == 0) {
        unset($participants[$key]);
      }
    }
  }

  return $event->seats - count($participants);
}

function sl7_event_access($op, $event = NULL, $account = NULL) {
  $rights = &drupal_static(__FUNCTION__, array());

  if (!empty($account)) {
    $account = is_object($account) ? $account : user_load($account);
  }
  else {
    $account = $GLOBALS['user'];
  }

  // User #1 has all privileges.
  if ($account->uid == 1) {
    return TRUE;
  }

  if (!$event) {
    if ($op == 'manage' && user_access("sl7_event $op", $account)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  if ($event) {
    $event = is_object($event) ? $event : sl7_event_load($event);
    $eid = $event->eid;
  }

  if (isset($rights[$account->uid][$eid][$op])) {
    return $rights[$account->uid][$eid][$op];
  }

  if (user_access('administer sl7_event', $account)) {
    $rights[$account->uid][$eid][$op] = TRUE;
    return TRUE;
  }
  else {
    if (user_access("sl7_event $op", $account)) {
      $rights[$account->uid][$eid][$op] = TRUE;
      return TRUE;
    }
  }

  return FALSE;
}

/**
 * Проверка доступа на страницу личного кабинета.
 */
function sl7_event_access_user_page($current_user) {
  $account = $GLOBALS['user'];

  // User #1 has all privileges.
  if ($account->uid == 1) {
    return TRUE;
  }

  if (user_access('sl7_order any view', $account)) {
    return TRUE;
  }

  if (user_access('sl7_order own view', $account) && $current_user->uid == $account->uid) {
    return TRUE;
  }

  return FALSE;
}