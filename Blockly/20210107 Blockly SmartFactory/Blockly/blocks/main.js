'use strict';

goog.provide('Blockly.Blocks.main');  // Deprecated
goog.provide('Blockly.Constants.main');

goog.require('Blockly.Blocks');



Blockly.Blocks['main_start'] = {
init: function(){  
        this.jsonInit({
                "type": "main_start",
                "message0": "start %1",
                "args0": [
                   {
                       "type": "input_statement", 
                       "name": "DO"
                   }
                ],
                "category": null,
                "colour": "%{BKY_LOGIC_HUE}",
                "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
                "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
                "deletable" : false
            });
        this.setDeletable(false);                   // main block can't be deleted

    }
}


Blockly.Blocks['main_loop'] = {
init: function(){  
        this.jsonInit({
                "type": "main_loop",
                "message0": "loop %1",
                "args0": [
                   {
                       "type": "input_statement", 
                       "name": "DO"
                   }
                ],
                "category": null,
                "colour": "%{BKY_LOGIC_HUE}",
                "tooltip": "%{BKY_LOGIC_BOOLEAN_TOOLTIP}",
                "helpUrl": "%{BKY_LOGIC_BOOLEAN_HELPURL}",
                "deletable" : false
            });
        this.setDeletable(false);                   // main block can't be deleted

    }
}