"use strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logica";
Blockly.Msg.CAT_LOOPS                     = "Lussen";
Blockly.Msg.CAT_TIME                      = "Tijd";
Blockly.Msg.CAT_MATH                      = "Wiskunde";
Blockly.Msg.CAT_MOVEMENT                  = "Beweging";
Blockly.Msg.CAT_IO                        = "I/O";
Blockly.Msg.CAT_VARIABLES                 = "Variabelen";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Getal";

// hardcoded blocks
Blockly.Msg.BL_IF_ELSE_IF                 = "als";
Blockly.Msg.BL_IF_ELSE_THEN               = "doe";
Blockly.Msg.BL_IF_ELSE_ELSE               = "anders doe";
Blockly.Msg.BL_NEGATE                     = "niet %1";
Blockly.Msg.BL_LED                        = "zet LED %1 %2";
Blockly.Msg.BL_BUTTON                     = "knop %1 is ingedrukt";
Blockly.Msg.BL_WHILE					  = "zolang %1 herhaal %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "voor %1 keer";
Blockly.Msg.BL_REPEAT_DO				  = "heerhaal";
Blockly.Msg.BL_REPEAT_FOREVER			  = "herhaal voor altijd";

// jumptable blocks
Blockly.Msg.BL_WAIT_MS                    = "wacht voor %1 milliseconden";
Blockly.Msg.BL_WAIT_1_SEC                 = "wacht voor 1 seconde";
Blockly.Msg.BL_MOVE_TO_IDLE               = "ga naar rust positie";
Blockly.Msg.BL_MOVE_TO_UP                 = "ga naar omhoog positie";
Blockly.Msg.BL_PRINT_NUMBER               = "print getal %1";
Blockly.Msg.BL_INVERT                     = "-%1";
Blockly.Msg.BL_WAIT_REACHED               = "wacht tot het doel is bereikt";
Blockly.Msg.BL_ENABLE_SERVOS              = "zet servos aan %1";
Blockly.Msg.BL_SET_JOINT                  = "beweeg %1 naar %2";
Blockly.Msg.BL_MOVE_SMOOTH                = "ga naar %1° %2° %3° %4° %5° %6°";
Blockly.Msg.BL_ADD                        = "%1 + %2";
Blockly.Msg.BL_SUBTRACT                   = "%1 - %2";
Blockly.Msg.BL_MULTIPLY                   = "%1 * %2";
Blockly.Msg.BL_DIVIDE                     = "%1 / %2";
Blockly.Msg.BL_EQUAL                      = "%1 = %2";
Blockly.Msg.BL_BIGGER                     = "%1 > %2";
Blockly.Msg.BL_SMALLER                    = "%1 < %2";
Blockly.Msg.BL_BIGGER_OR_EQUAL            = "%1 >= %2";
Blockly.Msg.BL_SMALLER_OR_EQUAL           = "%1 <= %2";
Blockly.Msg.BL_OR                         = "%1 of %2";
Blockly.Msg.BL_AND                        = "%1 en %2";
Blockly.Msg.BL_XOR                        = "een van %1 en %2";


// other
Blockly.Msg.TXT_TRUE                      = "waar";
Blockly.Msg.TXT_FALSE                     = "niet waar";
Blockly.Msg.TXT_ON                        = "aan";
Blockly.Msg.TXT_OFF                       = "uit";

Blockly.Msg.TXT_CREATE_NUMBER             = "maak getal";
Blockly.Msg.TXT_CREATE_BOOL               = "maak boolean";

Blockly.Msg.TXT_BUILD					  = "bouw";
Blockly.Msg.TXT_LANGUAGE			      = "taal";
Blockly.Msg.TXT_TITLE				      = "Arexx Robot Arm";