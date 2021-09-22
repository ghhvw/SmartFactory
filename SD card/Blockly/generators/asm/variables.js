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

/**
 * @fileoverview Generating asm for variable blocks.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.asm.variables');

goog.require('Blockly.asm');


// for numbers
Blockly.asm['variables_get_number'] = function(block) {
  // Variable getter.
  var variable = Blockly.asm.variableDB_.getName(block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
	var code = Blockly.asm.indent + "lds r24, " + variable + "_L" + '\n' +
						 Blockly.asm.indent + "lds r25, " + variable + "_H" + '\n';
	
  return [code, Blockly.asm.ORDER_ATOMIC];
};


Blockly.asm['variables_set_number'] = function(block) {
  // Variable setter.
  var valueCode = Blockly.asm.valueToCode(block, 'VALUE', 0) || '';	// <- default value for when no block is connected
  var varName = Blockly.asm.variableDB_.getName(block.getFieldValue('VAR'),
      Blockly.Variables.NAME_TYPE);
  
	
  return valueCode +
				 Blockly.asm.indent + "sts " + varName + "_L, r24\n" +
				 Blockly.asm.indent + "sts " + varName + "_H, r25\n";
};



// for robot positions
Blockly.asm['variables_get_Boolean'] = function(block) {
  // Variable getter.
  var variable = Blockly.asm.variableDB_.getName(block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
	var code = Blockly.asm.indent + "lds r24, " + variable + '\n';    
	
  return [code, Blockly.asm.ORDER_ATOMIC];
};

Blockly.asm['variables_set_Boolean'] = function(block) {
  // Variable setter.
  var valueCode = Blockly.asm.valueToCode(block, 'VALUE', 0) || '';             
  var varName = Blockly.asm.variableDB_.getName(block.getFieldValue('VAR'),
      Blockly.Variables.NAME_TYPE);
	
	return valueCode + 
				 Blockly.asm.indent + "sts " + varName + ', r24\n';
};