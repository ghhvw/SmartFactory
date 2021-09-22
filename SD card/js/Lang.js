

var LangHandler = {}; 
LangHandler.LANGUAGE_NAME = {
  'en' : 'English',
  'nl' : 'Nederlands',
  'fr' : 'Français',
  'de' : 'Deutsch'
};


LangHandler.getStringParamFromUrl = function(name, defaultValue) {
  var val = location.search.match(new RegExp('[?&]' + name + '=([^&]+)'));
  return val ? decodeURIComponent(val[1].replace(/\+/g, '%20')) : defaultValue;
};


LangHandler.getLang = function() {
  var lang = LangHandler.getStringParamFromUrl('lang', '');
  if (LangHandler.LANGUAGE_NAME[lang] === undefined) {
    // Default to English.
    lang = 'en';
  }
  return lang;
};


LangHandler.LANG = LangHandler.getLang();


LangHandler.loadBlocks = function() {
  try {
    var loadOnce = window.sessionStorage.loadOnceBlocks;
  } catch(e) {
    // Firefox sometimes throws a SecurityError when accessing sessionStorage.
    // Restarting Firefox fixes this, so it looks like a bug.
    var loadOnce = null;
  }
  if ('BlocklyStorage' in window && window.location.hash.length > 1) {
    // An href with #key trigers an AJAX call to retrieve saved blocks.
    BlocklyStorage.retrieveXml(window.location.hash.substring(1));
  } else if (loadOnce) {
    // Language switching stores the blocks during the reload.
    delete window.sessionStorage.loadOnceBlocks;
    var xml = Blockly.Xml.textToDom(loadOnce);
    Blockly.Xml.domToWorkspace(xml, workspace);
  } else if (document.getElementById('startBlocks')) {
    Blockly.Xml.domToWorkspace(document.getElementById('startBlocks'), workspace);
    // Load the editor with default starting blocks.
    //var xml = Blockly.Xml.textToDom(defaultXml);
    //Blockly.Xml.domToWorkspace(xml, workspace);
  } else if ('BlocklyStorage' in window) {
    // Restore saved blocks in a separate thread so that subsequent
    // initialization is not affected from a failed load.
    window.setTimeout(BlocklyStorage.restoreBlocks, 0);
  }
};



        
LangHandler.changeLanguage = function() {
		  // Store the blocks for the duration of the reload.
		  // This should be skipped for the index page, which has no blocks and does
		  // not load Blockly.
		  // MSIE 11 does not support sessionStorage on file:// URLs.
		  if (typeof Blockly != 'undefined' && window.sessionStorage) {
			var xml = Blockly.Xml.workspaceToDom(workspace);
			var text = Blockly.Xml.domToText(xml);
			window.sessionStorage.loadOnceBlocks = text;
		  }

		  var languageMenu = document.getElementById('languageMenu');
		  var newLang = encodeURIComponent(
			  languageMenu.options[languageMenu.selectedIndex].value);
		  var search = window.location.search;
		  if (search.length <= 1) {
			search = '?lang=' + newLang;
		  } else if (search.match(/[?&]lang=[^&]*/)) {
			search = search.replace(/([?&]lang=)[^&]*/, '$1' + newLang);
		  } else {
			search = search.replace(/\?/, '?lang=' + newLang + '&');
		  }

		  window.location = window.location.protocol + '//' +
			  window.location.host + window.location.pathname + search;
};
  


LangHandler.insertIntoHTML = function()
{
	var elements = document.getElementsByClassName("langtxt");

	for(var i = 0; i < elements.length; i++)
	{
		elements[i].innerHTML = Blockly.Msg[elements[i].dataset.txt]; //Blockly.Msg[elements[i].innerHTML];
	}
}


    
LangHandler.initLanguage = function() {
		  // Set the HTML's language and direction.
		  //var rtl = Code.isRtl();
		  //document.dir = rtl ? 'rtl' : 'ltr';
		  document.head.parentElement.setAttribute('lang', LangHandler.LANG);

		  // Sort languages alphabetically.
		  var languages = [];
		  for (var lang in LangHandler.LANGUAGE_NAME) {
			languages.push([LangHandler.LANGUAGE_NAME[lang], lang]);
		  }
		  var comp = function(a, b) {
			// Sort based on first argument ('English', 'Русский', '简体字', etc).
			if (a[0] > b[0]) return 1;
			if (a[0] < b[0]) return -1;
			return 0;
		  };
		  languages.sort(comp);
		  // Populate the language selection menu.
		  var languageMenu = document.getElementById('languageMenu');
		  languageMenu.options.length = 0;
		  for (var i = 0; i < languages.length; i++) {
			var tuple = languages[i];
			var lang = tuple[tuple.length - 1];
			var option = new Option(tuple[0], lang);
			if (lang == LangHandler.LANG) {
			  option.selected = true;
			}
			languageMenu.options.add(option);
		  }
		  languageMenu.addEventListener('change', LangHandler.changeLanguage, true);
  
		  // Inject language strings.
		  //document.title += ' ' + MSG['title'];
		  //document.getElementById('title').textContent = MSG['title'];
		  //document.getElementById('tab_blocks').textContent = MSG['blocks'];

		  //document.getElementById('linkButton').title = MSG['linkTooltip'];
		  //document.getElementById('runButton').title = MSG['runTooltip'];
		  //document.getElementById('trashButton').title = MSG['trashTooltip'];
  
          LangHandler.loadBlocks();

          if ('BlocklyStorage' in window) {
            // Hook a save function onto unload.
            BlocklyStorage.backupOnUnload(LangHandler.workspace);
          }
	
		  LangHandler.insertIntoHTML();
};

		
document.write('<script src="blockly/msg/js/' + LangHandler.LANG + '.js"></script>\n');
document.write('<script src="Languages/' + LangHandler.LANG + '.js"></script>\n');


function setButtonText() {
	setText("help_button", Blockly.Msg.TXT_HELP, "Help <button style='font-size:24px'>Button <i class='fas fa-info'></i>");
	setText("download_button", Blockly.Msg.TXT_SAVE, "Save");
	setText("load_button", Blockly.Msg.TXT_LOAD, "Load");
	setText("build_button", Blockly.Msg.TXT_BUILD, "Build");
	setText("stop_button", Blockly.Msg.TXT_STOP, "Stop");
	setText("start_button", Blockly.Msg.TXT_START, "Start");
	setText("test_button", Blockly.Msg.TXT_TEST, "Test");
	setText("layout_button", Blockly.Msg.TXT_Layout, "Lay-Out");
	
}


function setText(elem, translation, def) {
	if (translation != undefined) {
		document.getElementById(elem).textContent = translation;
	} else {
		document.getElementById(elem).textContent = def; //default bij missende vertaling
		console.error("missing translation for element: \""+elem+"\", using default");
	}
}