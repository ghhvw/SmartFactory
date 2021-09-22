/**
 * @license
 * Visual Blocks Language
 *
 * Copyright 2012 Google Inc.
 * https://developers.google.com/blockly/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';

goog.provide('Blockly.asm.math');

goog.require('Blockly.asm');



Blockly.asm['math_number'] = function(block) {
  // Numeric value.
  var number = parseInt(block.getFieldValue('NUM'));

	var code = Blockly.asm.indent + "ldi R24, "+(number & 0xFF)+"\n" + 
						 Blockly.asm.indent + "ldi R25, "+((number >>> 8) & 0xff)+"\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};

/*
Blockly.asm['math_add'] = function(block) {
	
  var argument0code = Blockly.asm.valueToCode(block, 'A');
  var argument1code = Blockly.asm.valueToCode(block, 'B');
  
	var indent = Blockly.asm.indent;
	
	var code = 	argument0code +
							indent + "push r24\n" +
							indent + "push r25\n" +
							argument1code +
							indent + "pop r23\n" +
							indent + "pop r22\n" +
							indent + "add r24, r22\n" +
							indent + "adc r25, r23\n";
	
	return [code, Blockly.asm.ORDER_ATOMIC];
};


Blockly.asm['math_subtract'] = function(block) {
	
  var argument0code = Blockly.asm.valueToCode(block, 'A');
  var argument1code = Blockly.asm.valueToCode(block, 'B');
  
	var indent = Blockly.asm.indent;
	
	var code = 	argument1code +
							indent + "push r24\n" +
							indent + "push r25\n" +
							argument0code +
							indent + "pop r23\n" +
							indent + "pop r22\n" +
							indent + "sub r24, r22\n" +
							indent + "sbc r25, r23\n";
	
	return [code, Blockly.asm.ORDER_ATOMIC];
};*/