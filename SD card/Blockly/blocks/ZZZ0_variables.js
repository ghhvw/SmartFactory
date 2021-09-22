/**
 * @license
 * Visual Blocks Editor
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
 * @fileoverview Variable blocks for Blockly.

 * This file is scraped to extract a .json file of block definitions. The array
 * passed to defineBlocksWithJsonArray(..) must be strict JSON: double quotes
 * only, no outside references, no functions, no trailing commas, etc. The one
 * exception is end-of-line comments, which the scraper will remove.
 * @author fraser@google.com (Neil Fraser)
 */
'use strict';

goog.provide('Blockly.Blocks.variables');  // Deprecated.
goog.provide('Blockly.Constants.Variables');

goog.require('Blockly.Blocks');


/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.VARIABLES_HUE.
 * @readonly
 */
Blockly.Constants.Variables.HUE = 330;
/** @deprecated Use Blockly.Constants.Variables.HUE */
Blockly.Blocks.variables.HUE = Blockly.Constants.Variables.HUE;

Blockly.defineBlocksWithJsonArray([  // BEGIN JSON EXTRACT
  // Block for variable getter.
  {
    "type": "variables_get",
    "message0": "%1",
    "args0": [
    {
        "type": "field_variable",
        "name": "VAR",
        "variable": "%{BKY_VARIABLES_DEFAULT_NAME}"
    }],
    "output": null,
    "colour": "%{BKY_VARIABLES_HUE}",
    "helpUrl": "%{BKY_VARIABLES_GET_HELPURL}",
    "tooltip": "%{BKY_VARIABLES_GET_TOOLTIP}",
    "extensions": ["contextMenu_variableSetterGetter"]
  },
  // Block for variable setter.
  {
    "type": "variables_set",
    "message0": "%{BKY_VARIABLES_SET}",
    "args0": [
      {
        "type": "field_variable",
        "name": "VAR",
        "variable": "%{BKY_VARIABLES_DEFAULT_NAME}"
      },
      {
        "type": "input_value",
        "name": "VALUE"
      }
    ],
    "previousStatement": null,
    "nextStatement": null,
    "colour": "%{BKY_VARIABLES_HUE}",
    "tooltip": "%{BKY_VARIABLES_SET_TOOLTIP}",
    "helpUrl": "%{BKY_VARIABLES_SET_HELPURL}",
    "extensions": ["contextMenu_variableSetterGetter"]
  },

  
    
    // setter for number
	{
    "type": "variables_set_number",
    "message0": "%{BKY_VARIABLES_SET}",
    "args0": [
    {
        "type": "field_variable",
        "name": "VAR",
        "variable": "%{BKY_VARIABLES_DEFAULT_NAME}",
        "variableTypes": ["Number"]
    },
    {
        "type": "input_value",
        "name": "VALUE",
        "check": "Number"    
    }],
      "previousStatement": null,
      "nextStatement": null,
      "colour": "%{BKY_MATH_HUE}"
    },
    
	
    
    // setter for boolean
    {
      "type": "variables_set_Boolean",
      "message0": "%{BKY_VARIABLES_SET}",
      "args0": [
        {
          "type": "field_variable",
          "name": "VAR",
          "variable": "%{BKY_VARIABLES_DEFAULT_NAME}",
          "variableTypes": ["Boolean"]
        },
        {
          "type": "input_value",
          "name": "VALUE",
          "check": "Boolean",
        }
      ],
      "previousStatement": null,
      "nextStatement": null,
       "colour": "#a55b5b"
    },
	
	
	
/*	// setter for colour
    {
      "type": "variables_selectcolour",
      "message0": "%{BKY_VARIABLES_SET}",
      "args0": [
        {
          "type": "field_variable",
          "name": "VAR",
          "variable": "%{BKY_VARIABLES_DEFAULT_NAME}",
          "variableTypes": ["Colour"] // Specifies what types to put in the dropdown
        },
        {
          "type": "input_value",
          "name": "VALUE",
          "check": "Colour", // Checks that the input value is of type "Colour"
        }
      ],
//	  "output": "Colour",
      "previousStatement": null,
      "nextStatement": null,
      "colour": "#ab7d1e"
    },*/
	
	
     
  
]);  // END JSON EXTRACT (Do not delete this comment.)


/*Blockly.Blocks['variables_selectcolour'] = {
  category: "IO",
  init: function() {
	this.setOutput(true, 'Colour');
	this.jsonInit({
      "type": "variables_select_colour",
      "message0": "%{BKY_BL_SELECTCOLOUR}",
      "colour": categories[this.category].colour,
      "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
      "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}"
    });
    var field = new Blockly.FieldColour('#ff0000');
    field.setColours(
	  ['#000000', '#0000ff', '#00ff00', '#00ffff', '#ff0000', '#ff00ff', '#ffff00',
//	  '#808080', '#800000', '#808000', '#008000', '#800080', '#008080', '#000080',
	  '#ffffff']
	);
    field.setColumns(4);
    this.appendDummyInput()
        .appendField(field, 'VAR');
  }
}*/


Blockly.Blocks["variables_get_Boolean"] = {
  init: function() {
    this.setOutput(true, 'Boolean');
    this.setColour("#a55b5b");
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Boolean'));
    this.appendDummyInput().appendField(varDropDown, 'VAR');
  }
};


Blockly.Blocks["variables_set_Boolean"] = {
  init: function() {
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour("#a55b5b");
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Boolean'));
    this.appendDummyInput().appendField('set ').appendField(varDropDown, 'VAR').appendField(' to ');
    this.appendValueInput('VALUE').setCheck('Boolean');
  }
};


Blockly.Blocks["variables_get_number"] = {
  init: function() {
    this.setOutput(true, 'Number');
    this.setColour(Blockly.Blocks.math.HUE);
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Number'));
    this.appendDummyInput().appendField(varDropDown, 'VAR');
  }
};


Blockly.Blocks["variables_set_number"] = {
  init: function() {
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(Blockly.Blocks.math.HUE);
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Number'));
    this.appendDummyInput().appendField('set ').appendField(varDropDown, 'VAR').appendField(' to ');
    this.appendValueInput('VALUE').setCheck('Number');
  }
};


/*Blockly.Blocks["variables_get_Colour"] = {
  init: function() {
    this.setOutput(true, 'Colour');
    this.setColour("#ab7d1e");
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Colour'));
    this.appendDummyInput()
		.appendField(varDropDown, 'VAR');
  }
};*/


/*Blockly.Blocks["variables_set_Colour"] = {
  init: function() {
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour("#ab7d1e");
    var varDropDown = new Blockly.FieldDropdown(varDropdownGenerator('Colour'));
    this.appendDummyInput()
		.appendField('set ')
		.appendField(varDropDown, 'VAR')
		.appendField(' to ');
    this.appendValueInput('VALUE').setCheck('Colour');
  }
};*/




function varDropdownGenerator(type)
{
    var options = [['placeholder','placeHolder']];
    
    var variables = workspace.getVariablesOfType(type);
    for (var i = 0, variable; variable = variables[i]; i++) {
        var varName = variable.name;
        options.push([ Blockly.asm.variableDB_.getName(varName,Blockly.Variables.NAME_TYPE), varName ]);
    }
    
    return options;
};




/**
 * Mixin to add context menu items to create getter/setter blocks for this
 * setter/getter.
 * Used by blocks 'variables_set' and 'variables_get'.
 * @mixin
 * @augments Blockly.Block
 * @package
 * @readonly
 */
Blockly.Constants.Variables.CUSTOM_CONTEXT_MENU_VARIABLE_GETTER_SETTER_MIXIN = {
  /**
   * Add menu option to create getter/setter block for this setter/getter.
   * @param {!Array} options List of menu options to add to.
   * @this Blockly.Block
   */
  customContextMenu: function(options) {
    // Getter blocks have the option to create a setter block, and vice versa.
    if (this.type == 'variables_get') {
      var opposite_type = 'variables_set';
      var contextMenuMsg = Blockly.Msg.VARIABLES_GET_CREATE_SET;
    } else {
      var opposite_type = 'variables_get';
      var contextMenuMsg = Blockly.Msg.VARIABLES_SET_CREATE_GET;
    }

    var option = {enabled: this.workspace.remainingCapacity() > 0};
    var name = this.getFieldValue('VAR');
    option.text = contextMenuMsg.replace('%1', name);
    var xmlField = goog.dom.createDom('field', null, name);
    xmlField.setAttribute('name', 'VAR');
    var xmlBlock = goog.dom.createDom('block', null, xmlField);
    xmlBlock.setAttribute('type', opposite_type);
    option.callback = Blockly.ContextMenu.callbackFactory(this, xmlBlock);
    options.push(option);
  }
};

Blockly.Extensions.registerMixin('contextMenu_variableSetterGetter',
  Blockly.Constants.Variables.CUSTOM_CONTEXT_MENU_VARIABLE_GETTER_SETTER_MIXIN);
