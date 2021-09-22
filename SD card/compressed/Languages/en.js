"üse strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logic";
Blockly.Msg.CAT_LOOPS                     = "Loops";
Blockly.Msg.CAT_TIME                      = "Time";
Blockly.Msg.CAT_MATH                      = "Math";
Blockly.Msg.CAT_MOVEMENT                  = "Movement";
Blockly.Msg.CAT_IO                        = "IO";
Blockly.Msg.CAT_VARIABLES                 = "Variables";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Number";


// hardcoded blocks
Blockly.Msg.BL_IF_ELSE_IF                 = "if";
Blockly.Msg.BL_IF_ELSE_IF                 = "if";
Blockly.Msg.BL_IF_ELSE_THEN               = "do";
Blockly.Msg.BL_IF_ELSE_ELSE               = "else do";
Blockly.Msg.BL_NEGATE                     = "not %1";
Blockly.Msg.BL_LED                        = "turn LED %1 %2";
Blockly.Msg.BL_BUTTON                     = "button %1 is pressed";
Blockly.Msg.BL_WHILE					  = "while %1 do %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "for %1 times";
Blockly.Msg.BL_REPEAT_DO				  = "do";
Blockly.Msg.BL_REPEAT_FOREVER			  = "repeat forever";

// 
Languages.BlockNames["controls_simple_if"]           = "if";
Languages.BlockNames["controls_ifelse"]              = "if-else";
Languages.BlockNames["Logic_boolean"]                = "boolean";
Languages.BlockNames["logic_negate"]                 = "logic inverter";
Languages.BlockNames["controls_repeat_ext"]          = "repeat n times";
Languages.BlockNames["controls_while"]               = "repeat while";
Languages.BlockNames["controls_repeat_forever"]      = "repeat forever";
Languages.BlockNames["math_number"]                  = "number";
Languages.BlockNames["io_button"]                    = "button";
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



// jumptable blocks
Blockly.Msg.BL_WAIT_MS                    = "wait for %1 milliseconds";
Blockly.Msg.BL_WAIT_1_SEC                 = "wait for 1 second";
Blockly.Msg.BL_MOVE_TO_IDLE               = "move to idle position";
Blockly.Msg.BL_MOVE_TO_UP                 = "move to up position";
Blockly.Msg.BL_PRINT_NUMBER               = "print number %1";
Blockly.Msg.BL_INVERT                     = "-%1";
Blockly.Msg.BL_WAIT_REACHED               = "wait until target is reached";
Blockly.Msg.BL_ENABLE_SERVOS              = "enable servos %1";
Blockly.Msg.BL_SET_JOINT                  = "move %1 to %2";
Blockly.Msg.BL_MOVE_SMOOTH                = "move to %1° %2° %3° %4° %5° %6°";
Blockly.Msg.BL_ADD                        = "%1 + %2";
Blockly.Msg.BL_SUBTRACT                   = "%1 - %2";
Blockly.Msg.BL_MULTIPLY                   = "%1 * %2";
Blockly.Msg.BL_DIVIDE                     = "%1 / %2";
Blockly.Msg.BL_EQUAL                      = "%1 = %2";
Blockly.Msg.BL_BIGGER                     = "%1 > %2";
Blockly.Msg.BL_SMALLER                    = "%1 < %2";
Blockly.Msg.BL_BIGGER_OR_EQUAL            = "%1 >= %2";
Blockly.Msg.BL_SMALLER_OR_EQUAL           = "%1 <= %2";
Blockly.Msg.BL_OR                         = "%1 or %2";
Blockly.Msg.BL_AND                        = "%1 and %2";
Blockly.Msg.BL_XOR                        = "One of %1 or %2";

// 
Languages.BlockNames["functions_wait_ms"]           = "wait milliseconds";
Languages.BlockNames["functions_wait1sec"]          = "wait 1 second";
Languages.BlockNames["functions_moveToIdle"]        = "move to idle position";
Languages.BlockNames["functions_moveToUp"]          = "move to up position";
Languages.BlockNames["functions_PrintNums"]         = "print number";
Languages.BlockNames["functions_invert"]            = "invert";
Languages.BlockNames["functions_waitReached"]       = "wait until position reached";
Languages.BlockNames["functions_enableServos"]      = "enable servo's";
Languages.BlockNames["functions_setJoint"]          = "set joint";
Languages.BlockNames["functions_moveSmooth"]        = "move smooth";
Languages.BlockNames["functions_add"]               = "add";
Languages.BlockNames["functions_subtract"]          = "subtract";
Languages.BlockNames["functions_multiply"]          = "multiply";
Languages.BlockNames["functions_divide"]            = "divide";
Languages.BlockNames["functions_equal"]             = "equal";
Languages.BlockNames["functions_bigger"]            = "bigger";
Languages.BlockNames["functions_smaller"]           = "smaller";
Languages.BlockNames["functions_biggerOrEqual"]     = "bigger or equal";
Languages.BlockNames["functions_smallerOrEqual"]    = "smaller or equal";
Languages.BlockNames["functions_or"]                = "or";
Languages.BlockNames["functions_and"]               = "and";
Languages.BlockNames["functions_xor"]               = "xor";


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

// other
Blockly.Msg.TXT_TRUE                      = "true";
Blockly.Msg.TXT_FALSE                     = "false";
Blockly.Msg.TXT_ON                        = "on";
Blockly.Msg.TXT_OFF                       = "off";

Blockly.Msg.TXT_CREATE_NUMBER             = "create number";
Blockly.Msg.TXT_CREATE_BOOL               = "create boolean";

Blockly.Msg.TXT_BUILD					  = "build";
Blockly.Msg.TXT_LANGUAGE			      = "language";
Blockly.Msg.TXT_TITLE				      = "Arexx Robot Arm";