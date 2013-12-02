/**
 * taobao examples form js
 */
Drupal.behaviors.taobaoSDKExamples = {};

Drupal.behaviors.taobaoSDKExamples.attach = function(context, settings) {
  var $ = jQuery;
  $('#params_fieldset_wrapper .request-params').keyup(function() {
    // build string
    var query_arr = [];
    var event_target = $(this);
    $('#params_fieldset_wrapper .request-params').each(function(index, e) {
      var element_name = $(e).attr('name');
      var keyvalue = '';
      keyvalue = keyvalue + element_name + '=';
      keyvalue = keyvalue + $(e).val();
      query_arr.push(keyvalue);
    });
    
    $('#params_str').val(query_arr.join('&'));
  });
};
