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
 * @fileoverview Logic blocks for Blockly.
 *
 * This file is scraped to extract a .json file of block definitions. The array
 * passed to defineBlocksWithJsonArray(..) must be strict JSON: double quotes
 * only, no outside references, no functions, no trailing commas, etc. The one
 * exception is end-of-line comments, which the scraper will remove.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.Blocks.logic');  // Deprecated
goog.provide('Blockly.Constants.Logic');

goog.require('Blockly.Blocks');


/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.LOGIC_HUE.
 * @readonly
 */
Blockly.Constants.Logic.HUE = 210;
/** @deprecated Use Blockly.Constants.Logic.HUE */
Blockly.Blocks.logic.HUE = Blockly.Constants.Logic.HUE;



Blockly.Blocks['controls_simple_if'] = {
category: "Logic",
init: function(){        
        this.jsonInit({
		      "type": "controls_simple_if",
              "message0": "%{BKY_BL_IF_ELSE_IF} %1 %{BKY_BL_IF_ELSE_THEN} %2",
              "args0": [
                {
                  "type": "input_value",
                  "name": "CONDITION",
                  "check": "Boolean"
                },
                {
                  "type": "input_statement", 
                  "name": "DO"
                }
              ],
              "category": "Logic",
              "previousStatement": null,
              "nextStatement": null,
              "colour": categories[this.category].colour,
              "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
              "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
        });
   }
}


Blockly.Blocks['controls_ifelse'] = {
category: "Logic",
init: function(){        
        this.jsonInit({
		      "type": "controls_ifelse",										// <- de naam van het blok
              "message0": "%{BKY_BL_IF_ELSE_IF} %1",		// de text die in het blok komt (in dit geval een variabele)
              "args0": [																		// de eerste parameter: de conditie
                {
                  "type": "input_value",
                  "name": "CONDITION",
                  "check": "Boolean"
                }
              ],
              "message1": "%{BKY_BL_IF_ELSE_THEN} %1",	// het eerste code blok: de code die uitgevoerd wordt bij true
              "args1": [
                {
                  "type": "input_statement",
                  "name": "DO"
                }
              ],
              "message2": "%{BKY_BL_IF_ELSE_ELSE} %1",	// het tweede code blok: de code die uitgevoerd wordt bij false
              "args2": [
                {
                  "type": "input_statement",
                  "name": "ELSE"
                }
              ],
              "category": "Logic",
              "previousStatement": null,										// er kan een blok boven worden vastgemaakt
              "nextStatement": null,												// er kan een blok onder worden vastgemaakt
              "colour": categories[this.category].colour,
              "tooltip": "%{BKYCONTROLS_IF_TOOLTIP_2}",			// tooltip
              "helpUrl": "%{BKY_CONTROLS_IF_HELPURL}"
        });
   }
}



Blockly.Blocks['Logic_boolean'] = {
category: "Logic",
init: function(){        
        this.jsonInit({
          "type": "logic_boolean",
		  "message0": "%1",
		  "args0": [
			{
				"type": "field_dropdown",
				"name": "BOOL",
				"options": [
					["%{BKY_TXT_TRUE}", "1"],
					["%{BKY_TXT_FALSE}", "0"]
				]
			}
		  ],
          "category": "Logic",
          "output": "Boolean",
          "colour": categories[this.category].colour,
          "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
          "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}"
        });
   }
}



Blockly.Blocks['logic_negate'] = {
category: "Logic",
init: function(){        
        this.jsonInit({
          		"type": "logic_negate",
						"message0": "%{BKY_BL_NEGATE}",
						"args0": [
							{
								"type": "input_value",
								"name": "BOOL",
								"check": "Boolean"
							}
						],
        "category": "Logic",
		"output": "Boolean",
		"colour": categories[this.category].colour,
		"tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
		"helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}"
        });
   }
}

