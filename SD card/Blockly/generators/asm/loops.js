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
 * @fileoverview Generating asm for loop blocks.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.asm.loops');

goog.require('Blockly.asm');

Blockly.asm['controls_repeat_ext'] = function(block) {
	
	var numberCode = Blockly.asm.valueToCode(block, 'TIMES',0);
  var branch = Blockly.asm.statementToCode(block, 'DO'); 
		
  if(branch == undefined)
      branch = '';
		
  
	var startLabel = Blockly.asm.getUniqueLabel();
	var endLabel = Blockly.asm.getUniqueLabel();
	var indent = Blockly.asm.indent;	
		
  var code = 	indent + "push r16\n"+
							numberCode +
							indent + "mov	r16,	r24\n"+
							startLabel + ":\n"+
						 	branch+
							indent+"dec r16\n"+
							indent+"breq "+endLabel + "\n"+
							indent+ "jmp "+startLabel+"\n"+
							endLabel+":\n"+
							indent + "pop r16\n";
	
 return code;
};



Blockly.asm['controls_while'] = function(block) {
  // Do while loop.	
	var conditionCode = Blockly.asm.valueToCode(block, "CONDITION", 0);
	var body					= Blockly.asm.statementToCode(block, "DO");

	var indent = Blockly.asm.indent;
	var startLabel = Blockly.asm.getUniqueLabel();
	var skipLabel = Blockly.asm.getUniqueLabel();
	var endLabel = Blockly.asm.getUniqueLabel();
	
	var code = 	startLabel + ":\n" +
							conditionCode + "\n" +
						 	indent + "tst r24\n" +
							indent + "brne " + skipLabel + "\n" + 
							indent + "jmp " + endLabel + "\n" +
							skipLabel + ":\n" +
							body + "\n" +
							indent + "jmp " + startLabel + "\n" +
							endLabel + ":\n";
	
  return code;
};




Blockly.asm['controls_repeat_forever'] = function(block) {
  // Repeat forever
  var branch = Blockly.asm.statementToCode(block, 'DO');
    
  if(branch == undefined)
      branch = '';
  
  var label = Blockly.asm.getUniqueLabel();
    
  var code = 	label + ':\n' +
							branch+
							Blockly.asm.indent+'jmp '+label + "\n";
  return code;
};
