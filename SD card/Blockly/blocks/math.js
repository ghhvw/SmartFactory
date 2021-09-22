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
 * @fileoverview Math blocks for Blockly.
 *
 * This file is scraped to extract a .json file of block definitions. The array
 * passed to defineBlocksWithJsonArray(..) must be strict JSON: double quotes
 * only, no outside references, no functions, no trailing commas, etc. The one
 * exception is end-of-line comments, which the scraper will remove.
 * @author q.neutron@gmail.com (Quynh Neutron)
 */
'use strict';

goog.provide('Blockly.Blocks.math');  // Deprecated
goog.provide('Blockly.Constants.Math');

goog.require('Blockly.Blocks');


/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.MATH_HUE
 * @readonly
 */
Blockly.Constants.Math.HUE = 230;
/** @deprecated Use Blockly.Constants.Math.HUE */
Blockly.Blocks.math.HUE = Blockly.Constants.Math.HUE;



Blockly.Blocks['math_number'] = {
category: "Math",
init: function(){        
      this.jsonInit({
        "type": "math_number",
        "message0": "%1",
        "args0": [{
          "type": "field_number",
          "name": "NUM",
          "value": 0
        }],
        "output": "Number",
        "colour": categories[this.category].colour,
        "helpUrl": "%{BKY_MATH_NUMBER_HELPURL}",
        "tooltip": "%{BKY_MATH_NUMBER_TOOLTIP}",
      });
   }
}
