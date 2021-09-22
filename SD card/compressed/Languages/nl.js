"use strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logica ";
Blockly.Msg.CAT_LOOPS                     = "Lussen";
Blockly.Msg.CAT_TIME                      = "Tijd";
Blockly.Msg.CAT_MATH                      = "Wiskunde";
Blockly.Msg.CAT_MOVEMENT                  = "Beweging";
Blockly.Msg.CAT_IO                        = "I/O";
Blockly.Msg.CAT_VARIABLES                 = "Variabelen";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Getal";

// hardcoded blocks text
Blockly.Msg.BL_IF_ELSE_IF                 = "als";
Blockly.Msg.BL_IF_ELSE_THEN               = "doe";
Blockly.Msg.BL_IF_ELSE_ELSE               = "anders doe";
Blockly.Msg.BL_NEGATE                     = "niet %1";
Blockly.Msg.BL_LED                        = "zet LED %1 %2";
Blockly.Msg.BL_BUTTON                     = "knop %1 is ingedrukt";
Blockly.Msg.BL_WHILE					  = "zolang %1 herhaal %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "voor %1 keer";
Blockly.Msg.BL_REPEAT_DO				  = "herhaal";
Blockly.Msg.BL_REPEAT_FOREVER			  = "herhaal voor altijd";


// 
Languages.BlockNames["controls_simple_if"]           = "als";
Languages.BlockNames["controls_ifelse"]              = "als-anders";
Languages.BlockNames["Logic_boolean"]                = "boolean";
Languages.BlockNames["logic_negate"]                 = "logische inverter";
Languages.BlockNames["controls_repeat_ext"]          = "herhaal n keer";
Languages.BlockNames["controls_while"]               = "herhaal zolang";
Languages.BlockNames["controls_repeat_forever"]      = "herhaal altijd";
Languages.BlockNames["math_number"]                  = "getal";
Languages.BlockNames["io_button"]                    = "knop";
Languages.BlockNames["io_led"]                       = "led";


Languages.HelpTexts["controls_simple_if"]            = "Wacht voor een aantal milliseconden.";
Languages.HelpTexts["controls_ifelse"]               = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["Logic_boolean"]                 = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["logic_negate"]                  = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["controls_repeat_ext"]           = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["controls_while"]                = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["controls_repeat_forever"]       = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["math_number"]                   = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["io_button"]                     = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["io_led"]                        = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";


// hardcoded blocks help
Languages.BlockNames["functions_wait_ms"]           = "wacht milliseconden";
Languages.BlockNames["functions_wait1sec"]          = "wacht 1 seconde";
Languages.BlockNames["functions_moveToIdle"]        = "Ga naar rust positie";
Languages.BlockNames["functions_moveToUp"]          = "Ga naar rechtop positie";
Languages.BlockNames["functions_PrintNums"]         = "print getal";
Languages.BlockNames["functions_invert"]            = "negatief";
Languages.BlockNames["functions_waitReached"]       = "wacht tot positie is bereikt";
Languages.BlockNames["functions_enableServos"]      = "servo's aanzetten";
Languages.BlockNames["functions_setJoint"]          = "set joint";
Languages.BlockNames["functions_moveSmooth"]        = "move smooth";
Languages.BlockNames["functions_add"]               = "optellen";
Languages.BlockNames["functions_subtract"]          = "min";
Languages.BlockNames["functions_multiply"]          = "keer";
Languages.BlockNames["functions_divide"]            = "delen";
Languages.BlockNames["functions_equal"]             = "is gelijk aan";
Languages.BlockNames["functions_bigger"]            = "is groter dan";
Languages.BlockNames["functions_smaller"]           = "is kleiner dan";
Languages.BlockNames["functions_biggerOrEqual"]     = "is groter of gelijk aan";
Languages.BlockNames["functions_smallerOrEqual"]    = "is kleiner of geleik aan";
Languages.BlockNames["functions_or"]                = "of";
Languages.BlockNames["functions_and"]               = "en";
Languages.BlockNames["functions_xor"]               = "exlusieve of";


Languages.HelpTexts["functions_wait_ms"]            = "Wacht voor een aantal milliseconden.";
Languages.HelpTexts["functions_wait1sec"]           = "Wacht voor 1 seconde.";
Languages.HelpTexts["functions_moveToIdle"]         = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_moveToUp"]           = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_PrintNums"]          = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_invert"]             = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_waitReached"]        = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_enableServos"]       = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_setJoint"]           = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_moveSmooth"]         = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_add"]                = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_subtract"]           = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei."; 
Languages.HelpTexts["functions_multiply"]           = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_divide"]             = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_equal"]              = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_bigger"]             = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_smaller"]            = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_biggerOrEqual"]      = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_smallerOrEqual"]     = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_or"]                 = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_and"]                = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";
Languages.HelpTexts["functions_xor"]                = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";


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