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
 * @fileoverview Loop blocks for Blockly.
 *
 * This file is scraped to extract a .json file of block definitions. The array
 * passed to defineBlocksWithJsonArray(..) must be strict JSON: double quotes
 * only, no outside references, no functions, no trailing commas, etc. The one
 * exception is end-of-line comments, which the scraper will remove.
 * @author fraser@google.com (Neil Fraser)
 */
'use strict';

goog.provide('Blockly.Blocks.loops');  // Deprecated
goog.provide('Blockly.Constants.Loops');

goog.require('Blockly.Blocks');


/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.LOOPS_HUE
 * @readonly
 */
Blockly.Constants.Loops.HUE = 120;
/** @deprecated Use Blockly.Constants.Loops.HUE */
Blockly.Blocks.loops.HUE = Blockly.Constants.Loops.HUE;



Blockly.Blocks['controls_repeat_ext'] = {
category: "Loops",
init: function(){        
      this.jsonInit({
        "type": "controls_repeat_ext",
        "message0": "%{BKY_BL_REPEAT_TIMES}",
        "args0": [{
          "type": "input_value",
          "name": "TIMES",
          "check": "Number"
        }],
        "message1": "%{BKY_BL_REPEAT_DO} %1",
        "args1": [{
          "type": "input_statement",
          "name": "DO"
        }],
        "previousStatement": null,
        "nextStatement": null,
        "colour": categories[this.category].colour,
        "tooltip": "%{BKY_CONTROLS_REPEAT_TOOLTIP}",
        "helpUrl": "%{BKY_CONTROLS_REPEAT_HELPURL}",
      });
   }
}



Blockly.Blocks['controls_while'] = {
category: "Loops",
init: function(){        
      this.jsonInit({
        "type": "controls_while",
        "message0": "%{BKY_BL_WHILE}",
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
        "previousStatement": null,
        "nextStatement": null,
        "colour": categories[this.category].colour,
        "helpUrl": "%{BKY_CONTROLS_WHILEUNTIL_HELPURL}"
      });
   }
}



Blockly.Blocks['controls_repeat_forever'] = {
category: "Loops",
init: function(){        
      this.jsonInit({
        "type": "controls_repeat_forever",
        "inputsInline": false,
        "message0": "%{BKY_BL_REPEAT_FOREVER} %1",
        "args0": [{
          "type": "input_statement",
          "name": "DO"
        }],
        "category": "Loops",
        "previousStatement": null,
        "nextStatement": null,
        "colour": categories[this.category].colour,
        "tooltip": "%{BKY_CONTROLS_REPEAT_TOOLTIP}",
        "helpUrl": "%{BKY_CONTROLS_REPEAT_HELPURL}"
      });
   }
}
