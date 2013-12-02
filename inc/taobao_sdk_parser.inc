<?php

/**
 * @file
 * define all parser for parse result
 */
abstract class TaobaoSDKParser {
  protected $_data;

  public function __construct($data) {
    $this->_data = $data;
  }

  abstract protected function _parse();

  public function result() {
    $result = $this->_parse();

    if ($this->_fatchError($result)) {
      return FALSE;
    }
    return $result;
  }

  protected function _fatchError($result) {
    if (isset($result->error_response)) {
      $error = $result->error_response;
      watchdog('taobao_sdk', 'API call remote error, error code: !code subcode: !sub_code, error message: !message, !submessage',
        array('!code' => $error->code, '!message' => $error->msg, '!submessage' => $error->sub_msg, '!sub_code' => $error->sub_code),
        WATCHDOG_NOTICE);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}

/**
 * json parser
 */
class TaobaoSDKJSONParser extends TaobaoSDKParser {
  /**
   * parse json result from taobao sdk
   */
  protected function _parse() {
    return json_decode($this->_data);
  }
}

/**
 * xml parser
 */
class TaobaoSDKXMLParser extends TaobaoSDKParser {
  protected function _parse() {
    // todo implement xml result parse
    return '';
  }
}
