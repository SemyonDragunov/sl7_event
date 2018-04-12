<?php

class sl7_event_handler_sl7_event_check_paying extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['eid'] = 'eid';
    $this->additional_fields['free'] = 'free';
    $this->additional_fields['participant'] = array(
      'field' => 'sl7_event_participants_target_id',
      'table' => 'field_data_sl7_event_participants',
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $eid = $this->get_value($values, 'eid');
    $free = $this->get_value($values, 'free');
    $uid = $this->get_value($values, 'participant');
    $order_link = '';
    $pay_link = '';

    if (module_exists('sl7_payment')) {
      $order = sl7_event_get_participant_order($eid, $uid);

      if (isset($order->oid)) {
        $path = '/' . SL7_ORDER_PATH . '/' . $order->oid;
        $order_link = " | <a href='{$path}' target='_blank'>Платёж</a>";
        $pay_link = " | " . sl7_order_get_pay_link($order->oid);
      }
    }

    if (isset($order)) {
      if (is_object($order) && $order->state == 'paid') {
        return 'Оплачено' . $order_link;
      }
      elseif (!$free && !$order) {
        return 'Не оплачено' . $order_link . $pay_link;
      }
      elseif ($free) {
        return NULL;
      }
      else {
        return 'Не оплачено' . $order_link . $pay_link;
      }
    }
    else {
      return NULL;
    }
  }
}