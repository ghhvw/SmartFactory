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
 * @author Johan Ras
 */
'use strict';

goog.provide('Blockly.Blocks.Movement');  // Deprecated
goog.provide('Blockly.Constants.Movement');

goog.require('Blockly.asm');


/**
 * Common HSV hue for all blocks in this category.
 * Should be the same as Blockly.Msg.MATH_HUE
 * @readonly
 */
Blockly.Constants.Movement.HUE = 230;
/** @deprecated Use Blockly.Constants.Math.HUE */
Blockly.Blocks.Movement.HUE = Blockly.Constants.Movement.HUE;






Blockly.asm['movement_moveto'] = function(block) {
    var position        = Blockly.asm.valueToCode(block, 'position', Blockly.asm.ORDER_ATOMIC) || 'RobotJointPosition::idle';
    var speed           = Blockly.asm.valueToCode(block, 'speed', Blockly.asm.ORDER_ATOMIC) || '200';
    var varName         = Blockly.asm.variableDB_.getDistinctName('jointPosition', Blockly.Variables.NAME_TYPE);
    
    
    var code = 'robot.moveSmooth(' + position + ', (uint16_t)'+speed+');\n';
    
    return code;
};


Blockly.asm['movement_waitUnilPositionReached'] = function(block) {
   
    var code = 'robot.waitForPositionReached();\n';    
    return code;
};



Blockly.asm['movement_robotposition'] = function(block) {
    
  var value_gripperPos          = Blockly.asm.valueToCode(block, 'gripperPos', Blockly.asm.ORDER_ATOMIC);
  var value_wristRotationPos    = Blockly.asm.valueToCode(block, 'wristRotationPos', Blockly.asm.ORDER_ATOMIC);
  var value_wristPos            = Blockly.asm.valueToCode(block, 'wristPos', Blockly.asm.ORDER_ATOMIC);
  var value_elbowPos            = Blockly.asm.valueToCode(block, 'elbowPos', Blockly.asm.ORDER_ATOMIC);
  var value_shoulderPos         = Blockly.asm.valueToCode(block, 'shoulderPos', Blockly.asm.ORDER_ATOMIC);
  var value_shoulderRotationPos = Blockly.asm.valueToCode(block, 'shoulderRotationPos', Blockly.asm.ORDER_ATOMIC);
    
  var code =  'RobotJointPosition(Servo::degToValue(' + value_shoulderRotationPos + '), Servo::degToValue(' + value_shoulderPos  + '), Servo::degToValue(' + value_elbowPos + '), Servo::degToValue(' + value_wristPos + '), Servo::degToValue(' + value_wristRotationPos + '), Servo::degToValue(' + value_gripperPos + '))';
  return [code, Blockly.ORDER_ATOMIC];
};


Blockly.asm['movement_idleposition'] = function(block) {
   
    var code = 'RobotJointPosition::idle';    
    return [code, Blockly.ORDER_ATOMIC];
};


Blockly.asm['movement_upposition'] = function(block) {
   
    var code = 'RobotJointPosition::up';    
    return [code, Blockly.ORDER_ATOMIC];
};