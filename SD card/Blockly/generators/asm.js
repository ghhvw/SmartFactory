/**
 * @license
 * Visual Blocks Language
 *
 * Copyright 2015 Google Inc.
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
 * @fileoverview Helper functions for generating asm for blocks.
 * @author daarond@gmail.com (Daaron Dwyer)
 */
'use strict';

goog.provide('Blockly.asm');

goog.require('Blockly.Generator');


/**
 * asm code generator.
 * @type {!Blockly.Generator}
 */
Blockly.asm = new Blockly.Generator('asm');

// turn of auto indentation
Blockly.asm.INDENT = '';

// set a string for manual indentation
Blockly.asm.indent = '  ';


Blockly.asm.ORDER_ATOMIC = 0;


/**
 * Initialise the database of variable names.
 * @param {!Blockly.Workspace} workspace Workspace to generate code from.
 */
Blockly.asm.init = function(workspace) {
  // Create a dictionary of definitions to be printed before the code.
  Blockly.asm.definitions_ = Object.create(null);
  // Create a dictionary mapping desired function names in definitions_
  // to actual function names (to avoid collisions with user functions).
  Blockly.asm.labelCount = 0;

  if (!Blockly.asm.variableDB_) {
    Blockly.asm.variableDB_ =
        new Blockly.Names(Blockly.asm.RESERVED_WORDS_, '');
  } else {
    Blockly.asm.variableDB_.reset();
  }
	
  Blockly.asm.definitions_['variables'] = Blockly.asm.genVariableDefinitions();
};

/**
 * Prepend the generated code with the variable definitions.
 * @param {string} code Generated code.
 * @return {string} Completed code.
 */
Blockly.asm.finish = function(code) {
  // Convert the definitions dictionary into a list.
  var definitions = [];
  for (var name in Blockly.asm.definitions_) {
    definitions.push(Blockly.asm.definitions_[name]);
  }
  // Clean up temporary data.
  delete Blockly.asm.definitions_;
  delete Blockly.asm.functionNames_;
  delete Blockly.asm.labelCount;
  Blockly.asm.variableDB_.reset();
  return definitions.join('\n\n') + '\n\n\n' + code;
};

/**
 * Naked values are top-level blocks with outputs that aren't plugged into
 * anything.  A trailing semicolon is needed to make this legal.
 * @param {string} line Line of generated code.
 * @return {string} Legal line of code.
 */
Blockly.asm.scrubNakedValue = function(line) {
  return line;
};

/**
 * Encode a string as a properly escaped asm string, complete with
 * quotes.
 * @param {string} string Text to encode.
 * @return {string} asm string.
 * @private
 */
Blockly.asm.quote_ = function(string) {
  string = string.replace(/\\/g, '\\\\')
                 .replace(/\n/g, '\\\n')
                 .replace(/'/g, '\\\'');
  return '\'' + string + '\'';
};

/**
 * Common tasks for generating asm from blocks.
 * Handles comments for the specified block and any connected value blocks.
 * Calls any statements following this block.
 * @param {!Blockly.Block} block The current block.
 * @param {string} code The asm code created for this block.
 * @return {string} asm code with comments and subsequent blocks added.
 * @private
 */
Blockly.asm.scrub_ = function(block, code) {
	
  var commentCode = '';
  // Only collect comments for blocks that aren't inline.
  if (!block.outputConnection || !block.outputConnection.targetConnection) {
    // Collect comment for this block.
    var comment = block.getCommentText();
    comment = Blockly.utils.wrap(comment, Blockly.asm.COMMENT_WRAP - 3);
    if (comment) {
      commentCode += Blockly.asm.prefixLines(comment, '// ') + '\n';
    }
    // Collect comments for all value arguments.
    // Don't collect comments for nested statements.
    for (var i = 0; i < block.inputList.length; i++) {
      if (block.inputList[i].type == Blockly.INPUT_VALUE) {
        var childBlock = block.inputList[i].connection.targetBlock();
        if (childBlock) {
          var comment = Blockly.asm.allNestedComments(childBlock);
          if (comment) {
            commentCode += Blockly.asm.prefixLines(comment, '// ');
          }
        }
      }
    }
  }
  var nextBlock = block.nextConnection && block.nextConnection.targetBlock();
  var nextCode = Blockly.asm.blockToCode(nextBlock);
  return commentCode + code + nextCode;
};



Blockly.asm.genVariableDefinitions = function()
{
	var address = ramAddress;
	var code = "; variables\n"
  var variables = Blockly.Variables.allVariables(workspace);
	
	for (var i = 0, variable; variable = variables[i]; i++) {
    var varName = variable.name;
		var UniqueName =  Blockly.asm.variableDB_.getName(varName, Blockly.Variables.NAME_TYPE);
		
		if(variable.type == "Number")
	  {
				code += ".equ " + UniqueName + "_H = 0x" + wordToHexText(address) + "\n";
				code += ".equ " + UniqueName + "_L = 0x" + wordToHexText(address+1) + "\n";
		}
		else
		{
    		code += ".equ " + UniqueName + " = 0x" + wordToHexText(address) + "\n";
		}
		
		address += CppTypeSizes[variable.type];
  }
	
	return code;
}



// Label data
Blockly.asm.getUniqueLabel = function()
{
    Blockly.asm.labelCount++;
    return 'label_'+(Blockly.asm.labelCount-1);
}


/**
 * this file has been adjusted by Arexx Engineering to work with assembly code.
 * author: Johan Ras
 */