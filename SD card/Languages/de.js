"use strict";

var Languages = {};
Languages.BlockNames = {};
Languages.HelpTexts = {};

// categories
Blockly.Msg.CAT_LOGIC                     = "Logik";
Blockly.Msg.CAT_LOOPS                     = "Schleifen";
Blockly.Msg.CAT_TIME                      = "Zeit";
Blockly.Msg.CAT_MATH                      = "Mathematik";
Blockly.Msg.CAT_MOVEMENT                  = "Bewegung";
Blockly.Msg.CAT_IO                        = "I/O";
Blockly.Msg.CAT_VARIABLES                 = "Variablen";

// variables
Blockly.Msg.VAR_BOOL                      = "Boolean";
Blockly.Msg.VAR_NUMBER                    = "Nummer";
Blockly.Msg.VAR_COLOUR                    = "Farbe";

// hardcoded blocks
Blockly.Msg.BL_IF_ELSE_IF                 = "wie";
Blockly.Msg.BL_IF_ELSE_THEN               = "tun";
Blockly.Msg.BL_IF_ELSE_ELSE               = "sonst tun";
Blockly.Msg.BL_NEGATE                     = "nicht %1";
Blockly.Msg.BL_LED                        = "LED einschalten %1 %2";
Blockly.Msg.BL_BUTTON                     = "taste %1 wird gedrückt";
Blockly.Msg.BL_WHILE					  = "solange %1 wiederholen %2";
Blockly.Msg.BL_REPEAT_TIMES				  = "für %1 mal";
Blockly.Msg.BL_REPEAT_DO				  = "wiederholen";
Blockly.Msg.BL_REPEAT_FOREVER			  = "für immer wiederholen";

// jumptable blocks
Blockly.Msg.BL_WAIT_MS                    = "warten für %1 milliesekunden";
Blockly.Msg.BL_WAIT_1_SEC                 = "1 sekunden warten";
Blockly.Msg.BL_MOVE_TO_IDLE               = "in die ruheposition gehen";
Blockly.Msg.BL_MOVE_TO_UP                 = "gehe nach die oben postion";
Blockly.Msg.BL_PRINT_NUMBER               = "Drucknummer %1";
Blockly.Msg.BL_INVERT                     = "-%1";
Blockly.Msg.BL_WAIT_REACHED               = "warten sie, bis das ziel erreicht ist";
Blockly.Msg.BL_ENABLE_SERVOS              = "servos einschalten %1";
Blockly.Msg.BL_SET_JOINT                  = "ziehen %1 nach %2";
Blockly.Msg.BL_MOVE_SMOOTH                = "gehe zu %1° %2° %3° %4° %5° %6°";
Blockly.Msg.BL_ADD                        = "%1 + %2";
Blockly.Msg.BL_SUBTRACT                   = "%1 - %2";
Blockly.Msg.BL_MULTIPLY                   = "%1 * %2";
Blockly.Msg.BL_DIVIDE                     = "%1 / %2";
Blockly.Msg.BL_EQUAL                      = "%1 = %2";
Blockly.Msg.BL_BIGGER                     = "%1 > %2";
Blockly.Msg.BL_SMALLER                    = "%1 < %2";
Blockly.Msg.BL_BIGGER_OR_EQUAL            = "%1 >= %2";
Blockly.Msg.BL_SMALLER_OR_EQUAL           = "%1 <= %2";
Blockly.Msg.BL_OR                         = "%1 oder %2";
Blockly.Msg.BL_AND                        = "%1 und %2";
Blockly.Msg.BL_XOR                        = "einer von %1 und %2";
Blockly.Msg.BL_TOGGLELED                  = "schalter LED";
Blockly.Msg.BL_SETLED                     = "LED %1";
Blockly.Msg.BL_DIGITALREAD                = "digitales lesen %1";
Blockly.Msg.BL_MOVEBELT                   = "band bewegen %2 %1 mit geschwindigkeit %3";
Blockly.Msg.BL_STOPBELT                   = "stopband %1";
Blockly.Msg.BL_MOVESORTERARMDISTANCE      = "arm sortieren %1 %2 position(s)";
Blockly.Msg.BL_MOVESORTERARMINDEX         = "arm sortieren nach %1";
Blockly.Msg.BL_SORTERARMPOSITION          = "armposition sortieren";
Blockly.Msg.BL_SORTERARMREADY             = "sortierarm is fertig";
//Blockly.Msg.BL_MOVESORTERARM              = "move sorter arm %1";
//Blockly.Msg.BL_STOPSORTERARM              = "stop sorter arm";
Blockly.Msg.BL_MOVETURNTABLE              = "drehen drehteller %2 %1 mit der geschwindigkeit %3";
Blockly.Msg.BL_STOPTURNTABLE              = "stopp drehteller %1";
Blockly.Msg.BL_DEMOTESTBLOCK              = "Demo-Testblock"; // Test code
Blockly.Msg.BL_STOPDEMOTESTBLOCK          = "Stop Demo-Testblock"; // Test code
Blockly.Msg.BL_MOVEELEVATOR               = "fahrstuhl bewegen %1";
Blockly.Msg.BL_STOPELEVATOR               = "aufzug anhalten";
Blockly.Msg.BL_ELEVATORREADY              = "aufzug ist fertig";
Blockly.Msg.BL_BEWEEGLIFT                 = "fahrstuhl bewegen  %1"; // Nieuwe lift code
Blockly.Msg.BL_STOPLIFFT                  = "stop lift"; // Nieuwe lift code
Blockly.Msg.BL_LIFTISKLAAR                = "der aufzug ist fertig"; // Nieuwe lift code
Blockly.Msg.BL_SOLENOID                   = "magnet no.%1 %2";
Blockly.Msg.BL_PULSESOLENOID              = "solenoid no.%1 pulse";
Blockly.Msg.BL_ANALOGREAD                 = "analog lesen%1";
Blockly.Msg.BL_READSHARPSENSOR            = "scharfer sensor %1";
Blockly.Msg.BL_OPTOCOUPLERREAD            = "optokoppler lesen %1";
Blockly.Msg.BL_SELECTCOLOUR               = "%1";
Blockly.Msg.BL_READCOLOURSENSOR           = "farbsensor";
Blockly.Msg.BL_COMPARECOLOURS             = "farbe %1 == farbe %2";

// hardcoded blocks help
//logic
Languages.BlockNames["steuert_einfach_wenn"]        = "wenn-ja";
Languages.BlockNames["steuert_wennsonst"]           = "wenn-sonst tun";
Languages.BlockNames["Logik_boolean"]               = "wahr/falsch: boolean";
Languages.BlockNames["logisches_negat"]             = "nicht: logischer wechselrichter";
Languages.BlockNames["funktionen_oder"]             = "oder";
Languages.BlockNames["funktionen_und"]              = "und";
Languages.BlockNames["funktionen_xor"]              = "einer von-oder : xor";
//loops
Languages.BlockNames["kontrollen_wiederholen_ext"]  = "für-zeiten-tun";
Languages.BlockNames["steuert_während"]             = "während-tun";
Languages.BlockNames["kontrollen_wiederholen_sich_für_immer"] = "für immer wiederholen";
//time
Languages.BlockNames["funktionen_warten_ms"]        = "warten sie n millisekunden";
Languages.BlockNames["funktionen_warten1sek"]       = "1 sekunde warten";
//math
Languages.BlockNames["mathematische_zahl"]          = "0 : zahl";
Languages.BlockNames["funktionen_invertieren"]      = "- : invertieren";
Languages.BlockNames["funktionen_hinzufügen"]       = "+ : hinzufügen";
Languages.BlockNames["funktionen_subtrahieren"]     = "- : subtrahieren";
Languages.BlockNames["funktionen_multiplizieren"]   = "* : multiplizieren";
Languages.BlockNames["funktionen_teilen"]           = "/ : teilen";
Languages.BlockNames["funktionen_gleich"]           = "== : gleich";
Languages.BlockNames["funktionen_größer"]            = "> : größer";
Languages.BlockNames["funktionen_kleiner"]           = "< : kleiner";
Languages.BlockNames["funktionen_größerOderOrGleich"] = ">= : größer oder gleich";
Languages.BlockNames["funktionen_kleinerOderGleich"] = "<= : kleiner oder gleich";
Languages.BlockNames["funktionen_Farbenvergleichen"] = "farbe-== farbe-";
//movement
Languages.BlockNames["funktionen_Gürtelbewegen"]	= "gürtel bewegen";
Languages.BlockNames["funktionen_StoppGürtel"]	    = "stopp gürtel";
Languages.BlockNames["funktionen_BewegenSiedenAbstandzwischendenSortierarmen"] = "Sortierarm - Position (en)";
Languages.BlockNames["funktionen_SortierArmIndexBewegen"] = "Sortierarm to-";
Languages.BlockNames["functions_SorterArmPosition"]	= "sorter arm position";
Languages.BlockNames["functions_SorterArmReady"]	= "sorter arm is ready";
Languages.BlockNames["functions_MoveTurntable"]		= "turn turntable, Round like a Record";
Languages.BlockNames["functions_StopTurntable"]		= "stop turntable";
Languages.BlockNames["functions_DemoTestBlock"]     = "Demo Test Block"; // Test code
Languages.BlockNames["functions_StopDemoTestBlock"] = "Stop Demo Test Block"; // Test code
Languages.BlockNames["functions_MoveElevator"]		= "move elevator";
Languages.BlockNames["functions_StopElevator"]		= "stop elevator";
Languages.BlockNames["functions_ElevatorReady"]		= "elevator is ready";
Languages.BlockNames["functions_BeweegLift"]        = "beweeg lift"; // Nieuwe lift code
Languages.BlockNames["functions_StopLifft"]         = "stop lift"; // Nieuwe lift code
Languages.BlockNames["functions_LiftIsKlaar"]       = "de lift is klaar"; // Nieuwe lift code
Languages.BlockNames["functions_Solenoid"]			= "solenoid no.-";
Languages.BlockNames["functions_PulseSolenoid"]		= "solenoid no.-pulse";
//io
Languages.BlockNames["functions_SelectColour"]      = "colour";
Languages.BlockNames["io_button"]                   = "button-is pressed";
Languages.BlockNames["io_led"]                      = "turn LED-on/off";
Languages.BlockNames["functions_ToggleLED"]			= "toggle LED";
Languages.BlockNames["functions_LED"]               = "LED on/off";
Languages.BlockNames["functions_DigitalRead"]		= "digital read";
Languages.BlockNames["functions_AnalogRead"]		= "analog read";
Languages.BlockNames["functions_ReadSharpSensor"]   = "sharp sensor";
Languages.BlockNames["functions_OptocouplerRead"]   = "read optocoupler";
Languages.BlockNames["functions_ReadColourSensor"]  = "colour sensor";
//variables
Languages.BlockNames["variables_create_number"]     = "create number";
Languages.BlockNames["variables_get_number"]        = "get number";
Languages.BlockNames["variables_set_number"]        = "set number to";
Languages.BlockNames["variables_create_Boolean"]    = "create boolean";
Languages.BlockNames["variables_get_Boolean"]       = "get boolean";
Languages.BlockNames["variables_set_Boolean"]       = "set boolean to";
Languages.BlockNames["variables_create_Colour"]     = "create colour";
Languages.BlockNames["variables_get_Colour"]        = "get colour";
Languages.BlockNames["variables_set_Colour"]        = "set colour to";
//overig/ongebruikt \/
Languages.BlockNames["functions_MoveSorterArm"]		= "move sorter arm";
Languages.BlockNames["functions_StopSorterArm"]		= "stop sorter arm";
Languages.BlockNames["functions_moveToIdle"]        = "move to up";
Languages.BlockNames["functions_moveToUp"]          = "ga naar rechtop positie";
Languages.BlockNames["functions_PrintNums"]         = "print number";
Languages.BlockNames["functions_waitReached"]       = "wacht tot positie is bereikt";
Languages.BlockNames["functions_enableServos"]      = "servo's aanzetten";
Languages.BlockNames["functions_setJoint"]          = "set joint";
Languages.BlockNames["functions_moveSmooth"]        = "move smooth";

// hardcoded blocks help description
//logic
Languages.HelpTexts["controls_simple_if"]           = "Voer iets uit als de parameter waar is.";
Languages.HelpTexts["controls_ifelse"]              = "Is de parameter waar? Voer de eerste code uit. Zo niet, voer de tweede code uit.";
Languages.HelpTexts["Logic_boolean"]                = "Voer de waarde \"waar\" of \"onwaar\" in.";
Languages.HelpTexts["logic_negate"]                 = "Maakt van true --> false en van false --> true.";
Languages.HelpTexts["functions_or"]                 = "Hier komt \"waar\" uit wanneer één van de waarden van beide parameters waar is.";
Languages.HelpTexts["functions_and"]                = "Hier komt \"waar\" uit wanneer de waarden van beide parameters waar zijn.";
Languages.HelpTexts["functions_xor"]                = "Hier komt \"waar\" uit wanneer één van de waarden van de parameters waar is (en de andere waarde onwaar).";
//loops
Languages.HelpTexts["controls_repeat_ext"]          = "Voer de code een aantal keer uit, aangegeven door de parameter.";
Languages.HelpTexts["controls_while"]               = "Voer de code uit totdat de parameter onwaar is.";
Languages.HelpTexts["controls_repeat_forever"]      = "Eindeloze lus. Blijf voor altijd deze code uitvoeren.";
//time
Languages.HelpTexts["functions_wait_ms"]            = "Wacht voor een aantal milliseconden. Er zitten 1000 milliseconden in 1 seconde.";
Languages.HelpTexts["functions_wait1sec"]           = "Wacht voor 1 seconde.";
//math
Languages.HelpTexts["math_number"]                  = "Geef een nummer mee als parameter. Werkt goed met een \"" + Languages.BlockNames["controls_repeat_ext"] + "\".";
Languages.HelpTexts["functions_invert"]             = "Maak van een positief getal een negatief getal en andersom.";
Languages.HelpTexts["functions_add"]                = "Tel de getallen bij elkaar op.";
Languages.HelpTexts["functions_subtract"]           = "Trek de getallen van elkaar af.";
Languages.HelpTexts["functions_multiply"]           = "Vermenigvuldig de getallen.";
Languages.HelpTexts["functions_divide"]             = "Deel de getallen.";
Languages.HelpTexts["functions_equal"]              = "Vergelijk de parameters met elkaar. Wanneer ze gelijk zijn komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_bigger"]             = "Als de waarde van de eerste parameter groter is dan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_smaller"]            = "Als de waarde van de eerste parameter kleiner is dan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_biggerOrEqual"]      = "Als de waarde van de eerste parameter groter of gelijk is aan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_smallerOrEqual"]     = "Als de waarde van de eerste parameter kleiner of gelijk is aan die van de tweede parameter, dan komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
Languages.HelpTexts["functions_CompareColours"]     = "Als beide kleuren hetzelfde zijn komt hier \"waar\" uit. Zo niet, dan \"onwaar\".";
//movement
Languages.HelpTexts["functions_MoveBelt"]			= "Beweeg de band naar links of naar rechts.";
Languages.HelpTexts["functions_StopBelt"]			= "Stop de band.";
Languages.HelpTexts["functions_MoveSorterArmDistance"] = "Beweeg de sorteer arm een aantal posities naar links of naar rechts.";
Languages.HelpTexts["functions_MoveSorterArmIndex"] = "Beweeg de sorteer arm naar een positie.";
Languages.HelpTexts["functions_SorterArmPosition"]  = "Lees de positie van de sorteer arm.";
Languages.HelpTexts["functions_SorterArmReady"]     = "Sorteer arm is klaar voor een nieuwe beweging.";
Languages.HelpTexts["functions_MoveTurntable"]		= "Beweeg de draaischijf linksom of rechtsom.";
Languages.HelpTexts["functions_StopTurntable"]		= "Stop de draaischijf.";
Languages.HelpTexts["functions_DemoTestBlock"]      = "Demo Test Block, motor #8 moet gaan draaien.";
Languages.HelpTexts["functions_StopDemoTestBlock"]  = "Stop Demo Test Block, motor#8 moet stoppen met draaien.";
Languages.HelpTexts["functions_MoveElevator"]		= "Beweeg de lift, hij stopt automatisch. Gebruik blok \"" + Languages.BlockNames["functions_ElevatorReady"] + "\" om te checken of de lift klaar is.";
Languages.HelpTexts["functions_StopElevator"]		= "Stop de lift.";
Languages.HelpTexts["functions_ElevatorReady"]		= "Geeft \"waar\" terug wanneer de lift klaar is met bewegen.";
Languages.HelpTexts["functions_BeweegLift"]         = "Beweeg de lift omhoog of omlaag";
Languages.HelpTexts["functions_StopLifft"]          = "Stop de lift";
Languages.HelpTexts["functions_LiftIsKlaar"]        = "De lift is klaar voor gebruik";
Languages.HelpTexts["functions_Solenoid"]			= "Zet een solenoïde aan of uit. Zorg ervoor dat de solenoïde niet aan blijft staan, want dan wordt deze warm.";
Languages.HelpTexts["functions_PulseSolenoid"]		= "Zet een solenoïde kort aan.";
//io
Languages.HelpTexts["functions_SelectColour"]       = "Gebruik dit blok om sensorwaarden te vergelijken met een kleur.";
Languages.HelpTexts["io_button"]                    = "Lees een button uit. Werkt goed met een \"" + Languages.BlockNames["controls_simple_if"] + "\".";
Languages.HelpTexts["io_led"]                       = "Schakel een LED-lampje aan of uit.";
Languages.HelpTexts["functions_ToggleLED"]          = "Zet een LED-lampje aan als deze uit was, of uit als deze aan was.";
Languages.HelpTexts["functions_LED"]                = "Schakel een LED-lampje aan of uit.";
Languages.HelpTexts["functions_DigitalRead"]		= "Lees een digitale poort uit, bijvoorbeeld een van een schakelaar. Hier komt \"waar\" of \"onwaar\" uit. De poorten gaan van 1 t/m 12.";
Languages.HelpTexts["functions_AnalogRead"]			= "Lees een analoge poort uit, bijvoorbeeld die van de sharp sensor. Geeft een waarde terug van 0 t/m 255. De poorten gaan van 1 t/m 5.";
Languages.HelpTexts["functions_ReadSharpSensor"]	= "Lees de sharp sensor uit. Geeft een waarde terug in centimeters (4cm t/m 30cm). De sharp sensor is niet heel precies. De poorten hebben dezelfde range als blok \"" + Languages.BlockNames["functions_AnalogRead"] + "\".";
Languages.HelpTexts["functions_OptocouplerRead"]	= "Lees een optocoupler uit. Een optocoupler wordt gebruikt om een galvanische scheiding tussen circuits aan te brengen. Dit betekent dat er minder storing bij het lezen optreedt. De poorten gaan van 0 t/m 5.";
Languages.HelpTexts["functions_ReadColourSensor"]   = "Lees een kleursensor uit. Geeft een kleurwaarde terug.";
//variables
Languages.HelpTexts["variables_create_number"]      = "Maak een nummer-variabele. Stel deze in met blok \"" + Languages.BlockNames["variables_set_number"] + "\" en lees hem uit met blok \"" + Languages.BlockNames["variables_get_number"] + "\". Deze variabele kan ook een kleur opslaan.";
Languages.HelpTexts["variables_get_number"]         = "Lees een nummer-variabele uit.";
Languages.HelpTexts["variables_set_number"]         = "Stel een nummer-variabele in.";
Languages.HelpTexts["variables_create_Boolean"]     = "Maak een boolean-variabele. Stel deze in met blok \"" + Languages.BlockNames["variables_set_Boolean"] + "\" en lees hem uit met blok \"" + Languages.BlockNames["variables_get_Boolean"] + "\".";
Languages.HelpTexts["variables_get_Boolean"]        = "Lees een boolean-variabele uit.";
Languages.HelpTexts["variables_set_Boolean"]        = "Stel een boolean-variabele in.";
Languages.HelpTexts["variables_create_Colour"]      = "create colour";
Languages.HelpTexts["variables_get_Colour"]         = "get colour";
Languages.HelpTexts["variables_set_Colour"]         = "set colour to";
//overig/ongebruikt \/
Languages.HelpTexts["functions_MoveSorterArm"]		= "Beweeg de sorteerarm naar links of naar rechts. Let erop dat deze niet automatisch stopt, dus je moet er voor zorgen dat de arm stopt wanneer één van de schakelaars is ingedrukt. Bekijk het \"" + Languages.BlockNames["functions_DigitalRead"] + "\" blok.";
Languages.HelpTexts["functions_StopSorterArm"]		= "Stop de sorteerarm.";
Languages.HelpTexts["functions_PrintNums"]          = "Lorem ipsum dolor sit amet, nominavi quaerendum delicatissimi has no, altera indoctum eos ut. In mel velit phaedrum volutpat, est congue verear definitiones id. Aliquid maiestatis eam at, an quod elaboraret nec, cu pro iusto nostrud. Admodum inimicus eum ad. Duo an timeam dolorum iracundia. Qui enim graeco epicurei no, ea democritum temporibus eos, eu primis suscipiantur mei.";


// other
Blockly.Msg.TXT_TRUE                      = "wahr";
Blockly.Msg.TXT_FALSE                     = "nicht wahr";
Blockly.Msg.TXT_ON                        = "auf";
Blockly.Msg.TXT_OFF                       = "von";

Blockly.Msg.TXT_CREATE_NUMBER             = "nummer machen";
Blockly.Msg.TXT_CREATE_BOOL               = "boolean machen";

Blockly.Msg.TXT_HELP                      = "Hilfe";
Blockly.Msg.TXT_SAVE                      = "Speichern";
Blockly.Msg.TXT_LOAD                      = "Laden";
Blockly.Msg.TXT_BUILD					  = "Bauen";
Blockly.Msg.TXT_STOP                      = "Stop";
Blockly.Msg.TXT_START                     = "Start";
Blockly.Msg.TXT_LANGUAGE			      = "Sprache";
Blockly.Msg.TXT_TEST                      = "Prüfung";
Blockly.Msg.TXT_Layout                    = "Lay-out";
Blockly.Msg.TXT_TITLE                     = "Arexx Smart Factory";
Blockly.Msg.TXT_CONNECTED                 = "✔  in verbindung gebracht";
Blockly.Msg.TXT_DISCONNECTED              = "❌  Getrennt";
Blockly.Msg.TXT_ONTIMEOUT                 = "No (good) conection. Arange a good conection or restart the board ";
Blockly.Msg.TXT_ONERROR                   = "Unbekannter fehler, siehe konsole";
