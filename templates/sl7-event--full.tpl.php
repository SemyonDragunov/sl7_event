<div class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="wrapper">

    <div class="img">
      <img src="<?php print image_style_url('sl7_event_teaser', $variables['element']->sl7_event_image['und'][0]['uri']); ?>" />
    </div>

    <div class="property">

      <?php print render($category); ?>

      <?php if (isset($event_state) && 'end' == $event_state): ?>
        <div class="state">Мероприятие закончилось</div>
      <?php elseif (isset($event_state) && 'start' == $event_state): ?>
        <div class="state">Мероприятие уже началось</div>
      <?php elseif (isset($event_state) && 'no_seats' == $event_state): ?>
        <div class="state">Мест нет</div>
      <?php endif; ?>

      <?php print render($date); ?>

      <?php if (!isset($event_state) || (isset($event_state) && 'start' == $event_state)): ?>
        <?php if (module_exists('sl7_payment')): ?>
          <?php print render($amount); ?>
        <?php endif; ?>
        <?php print render($seats); ?>
      <?php endif; ?>
    </div>

  </div>

  <div class="wrapper">
    <?php print render($body); ?>
    <?php print render($map); ?>
  </div>

  <div class="form-participant">
    <?php print render($form); ?>
  </div>

</div>