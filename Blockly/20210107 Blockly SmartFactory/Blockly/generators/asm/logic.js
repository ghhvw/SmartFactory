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
 * @fileoverview Generating asm for logic blocks.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.asm.logic');

goog.require('Blockly.asm');



Blockly.asm['controls_simple_if'] = function(block) {
  // If/elseif/else condition.
  var conditionCode = Blockly.asm.valueToCode(block, "CONDITION", 0);
	var body					= Blockly.asm.statementToCode(block, "DO");

	var indent = Blockly.asm.indent;
	var skipLabel = Blockly.asm.getUniqueLabel();
	var endLabel = Blockly.asm.getUniqueLabel();
	
	var code = 	conditionCode + 
						 	indent + "tst r24\n" +
							indent + "brne " + skipLabel + "\n" + 
							indent + "jmp " + endLabel + "\n" +
							skipLabel + ":\n" +
							body +
							endLabel + ":\n";
	
  return code;
};



Blockly.asm['controls_ifelse'] = function(block) {
  // If/elseif/else condition.
  var conditionCode = Blockly.asm.valueToCode(block, "CONDITION", 0);	// vraag de code op die de conditie teruggeeft
	var trueBody			= Blockly.asm.statementToCode(block, "DO");			// vraag de true code op
	var falseBody			= Blockly.asm.statementToCode(block, "ELSE");		// vraag de false code op
	
	var indent = Blockly.asm.indent;
	var trueLabel 	= Blockly.asm.getUniqueLabel();										// maak een aantal unieke labels voor asm
	var falseLabel 	= Blockly.asm.getUniqueLabel();
	var endLabel		= Blockly.asm.getUniqueLabel();
	
	var code = 	conditionCode +																				// maak de uiteindelijke code voor het blok
						 	indent + "tst r24\n" +
							indent + "brne " + trueLabel + "\n" + 
							indent + "jmp " + falseLabel + "\n" +
							trueLabel + ":\n" +
							trueBody +
							indent + "jmp " + endLabel + "\n"+
							falseLabel + ":\n"+
							falseBody +
							endLabel + ":\n";
	
  return code;
};


Blockly.asm['logic_negate'] = function(block) {
	var indent = Blockly.asm.indent;
	
	var code = Blockly.asm.valueToCode(block, "BOOL", 0) +
						 indent + "ldi r18, 0x01\n" +
						 indent + "eor r24, r18\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};



Blockly.asm['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = "ldi r24, " + block.getFieldValue('BOOL') + "\n";
  return [code, Blockly.asm.ORDER_ATOMIC];
};