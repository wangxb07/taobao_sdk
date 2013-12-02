<?php

/**
 * @info
 * class file for TaobaoSDKRequest
 */

/**
 * @class
 * TaobaoSDKRequest
 */
class TaobaoSDKRequest {
  private $_url = '';
  private $_host = 'http://gw.api.taobao.com';
  private $_options = array();

  /**
   * build request by API information
   */
  static public function buildByInfo($info) {
    $request = new TaobaoSDKRequest();
    //TODO special config info
    return $request;
  }

  /**
   * construct method
   */
  public function __construct() {
    $this->_url = $this->_host . '/router/rest';
    $this->_options['headers']['User-Agent'] = 'Taobao SDK for Drupal';

    $this->_options['method'] = 'GET';
    $this->_options['data'] = '';
    $this->_options['max_redirects'] = 3;
    $this->_options['timeout'] = 30;
  }

  /**
   * The URL getter
   */
  public function getURL() {
    $this->_rebuildUrlAndOptions();
    return $this->_url;
  }

  /**
   * The options getter
   */
  public function getOptions() {
    $this->_rebuildUrlAndOptions();
    return $this->_options;
  }

  /**
   * The option setter
   */
  public function setOption($name, $value) {
    $this->_options[$name] = $value;
  }

  /**
   * rebuild url and options
   */
  private function _rebuildUrlAndOptions() {
    $params = array();

    $this->_generateSign();

    foreach ($this->_params as $key => $value) {
      $params[] = $key . '=' . urlencode($value);
    }

    $uri = @parse_url($this->_url);
    if ($this->_options['method'] == 'GET') {
      $this->_url = $this->_host . $uri['path'] . '?' . implode('&', $params);
    }
    else {
      $this->_options['data'] = implode('&', $params);
    }
  }

  /**
   * set request parameter
   * @param string $name
   * @param mixed $value
   * @param application|system string $level
   */
  public function setParameter($name, $value, $leval = 'application') {
    $this->_params[$name] = $value;
  }

  /**
   * Generate sign
   */
  private function _generateSign() {
    $secret = taobao_sdk_app_secret();
    unset($this->_params['sign']);
    ksort($this->_params);

    $signed = $secret;
    foreach ($this->_params as $k => $v) {
      if("@" != substr($v, 0, 1)) {
        $signed .= "$k$v";
      }
    }
    unset($k, $v);
    $signed .= $secret;

    $this->_params['sign'] = strtoupper(md5($signed));
  }
}
