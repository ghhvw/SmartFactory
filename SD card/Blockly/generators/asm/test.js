'use strict';

goog.provide('Blockly.asm.test');

goog.require('Blockly.asm');


Blockly.asm['test_setBit'] = function(block) {
	var reg = block.getFieldValue('register');
	var bit = block.getFieldValue('bit');
	var cmd = (block.getFieldValue('newValue') == '1') ? "sbi" : "cbi";

 	return Blockly.asm.indent + cmd + ' '+ reg + ", " + bit + "\n";
};



Blockly.asm['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = "ldi r24, " + block.getFieldValue('BOOL') + "\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};



Blockly.asm['logic_negate'] = function(block) {
	var indent = Blockly.asm.indent;
	
	var code = Blockly.asm.valueToCode(block, "BOOL") +
						 indent + "ldi r18, 0x01\n" +
						 indent + "eor r24, r18\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};



Blockly.asm['input_button'] = function(block) {
  // Boolean values true and false.
  var button = block.getFieldValue('BUTTON');
  var indent = Blockly.asm.indent;
	var code = 	indent + "clr r24\n" +
							indent + "sbis PINC, " + (button == '1' ? '4' : '5') + '\n' +
							indent + "ldi r24, 1\n";
	return [code, Blockly.asm.ORDER_ATOMIC];
};






Blockly.asm['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = Blockly.asm.indent + "ldi r24, " + block.getFieldValue('BOOL') + "\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};

