<?php


/**
 * Implements hook_taobao_api_info()
 */
function hook_taobao_api_info() {
  return array(
    'taobao.item.get' => array(
      'app_params' => array(
        'fields' => array(
          '#required' => TRUE,
        ),
        'num_iid' => array(
          '#required' => TRUE,
        ),
        'track_iid' => array(
          '#required' => TRUE,
        )
      ),
      'response_type' => 'TaobaoSDKResponse',
    ),
  );
}
