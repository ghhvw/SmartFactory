var blocklyArea = document.getElementById('blocklyArea');
var blocklyDiv = document.getElementById('blocklyDiv');


//generate the toolbox
var toolboxString = "";

function generateToolbox()
{
  var helpString = "";
  
  var blocklist = Blockly.Blocks;
  
  toolboxString += "<xml id=\"toolbox\" style=\"display: none\">\n";

  for(var category in categories)
  {
    toolboxString += "<category name=\""+categories[category].name+"\" colour=\""+categories[category].colour+"\">\n";
    if(Blockly.Msg["CAT_"+category.toUpperCase()] != undefined & Blockly.Msg["CAT_"+category.toUpperCase()] != null)
      helpString    += "<h1 class=\"block_info_category\">"+Blockly.Msg["CAT_"+category.toUpperCase()]+"</h1>\n";
    else
      console.error("missing translation for category: \""+category+"\"");
    
    for(var block in blocklist)
    {
      if(blocklist[block].category == category)
      {
        
        toolboxString += "<block type =\""+block+"\"></block>";
        
        if(Languages.BlockNames[block] != undefined && Languages.HelpTexts[block] != undefined)
        {
          helpString += "<div id=\""+block+"\" class=\"block_info\">\n"+
                        "<h3>"+Languages.BlockNames[block]+"</h3>\n"+
                        "<p>"+Languages.HelpTexts[block]+"</p>\n</div>";
        }
        else
        {
          if(Languages.BlockNames[block] == undefined)
            console.error("missing name translation for block: \""+block+"\"");
          if(Languages.HelpTexts[block] == undefined)
            console.error("missing help translation for block: \""+block+"\"");
        }
        
        
      }
    }
    
    toolboxString += "</category>";
  }
  
  // add the variable category
  toolboxString +=
    "<category name=\"%{BKY_CAT_VARIABLES}\" colour=\"330\">"+
        "<category name=\"%{BKY_VAR_NUMBER}\" colour=\"230\">"+
            "<button text=\"create number\" callbackKey=\"BUTTON_CREATE_NUMBER\"></button>"+
            "<block type=\"variables_get_number\"></block>"+
            "<block type=\"variables_set_number\"></block>"+
        "</category>"+
        "<category name=\"%{BKY_VAR_BOOL}\" colour=\"#a55b5b\">"+
            "<button text=\"create boolean\" callbackKey=\"BUTTON_CREATE_BOOLEAN\"></button>"+
            "<block type=\"variables_get_Boolean\"></block>"+
            "<block type=\"variables_set_Boolean\"></block>"+
        "</category>"+
    "</category>"+
    "</xml>";
  
  document.getElementById("help_content").innerHTML = helpString;
}



generateToolbox();



// change into Development mode
var enterDevMode = function()
{
  categories["DEV"] = {name: "DEVELOPMENT", colour: "#000000"};
  
  toolboxString = "";
  generateToolbox();
  
  workspace.updateToolbox(toolboxString);
}



// initialize the workspace
var workspace = Blockly.inject(blocklyDiv,	{ 
                                                toolbox: toolboxString,//document.getElementById('toolbox'),
                                                zoom : {
                                                        controls : true, 
                                                        wheel : true, 
                                                        startScale : 1, 
                                                        maxScale : 3, 
                                                        minScale : 0.3, 
                                                        scaleSpeed : 1.2
                                                    }, 
                                                grid:{
                                                    spacing: 30,
                                                    length: 1,
                                                    colour: '#888',
                                                    snap:false},
                                                trashcan: true
                                                
                                            });
        

    


var onresize = function (e) {
    // Compute the absolute coordinates and dimensions of blocklyArea.
    var element = blocklyArea;
    var x = 0;
    var y = 0;
    do {
        x += element.offsetLeft;
        y += element.offsetTop;
        element = element.offsetParent;
    } while (element);
    // Position blocklyDiv over blocklyArea.
    
    var a = 0;
    if(isOut){
        a = 500;
    }
    blocklyDiv.style.left = x + 'px';
    blocklyDiv.style.top = y + 'px';
    blocklyDiv.style.width = (blocklyArea.offsetWidth - a)+ 'px';
    blocklyDiv.style.height = blocklyArea.offsetHeight + 'px';
};
window.addEventListener('resize', onresize, false);
onresize();
Blockly.svgResize(workspace);


var hexFile = '';
var assemblyCode = '';
function myUpdateFunction(event) {
    Blockly.asm.init();
    let topBlocks = workspace.getTopBlocks();
    assemblyCode = "";
    let startCode = "";
    let loopCode = "";

    let startLabel = Blockly.asm.getUniqueLabel();
    let loopLabel = Blockly.asm.getUniqueLabel();

    for(let blockIndex in topBlocks)
    {
        let block = topBlocks[blockIndex];
        if(block.type === "main_start")
        {
            startCode = Blockly.asm.blockToCode(block);
        }
        if(block.type === "main_loop")
        {
            loopCode = Blockly.asm.blockToCode(block);
        }
    }

    assemblyCode = "; jumptable to pre-flashed functions\n"+
        jumpTableToCode() +
        "\n; register definitions\n" +
        controllerRegisters +
        "\n" +
        "; generated start code\n" +
        ".org 0x" + wordToHexText(blocklyAddress) + "\n" +
        startLabel + ':\n' + startCode +
        "\n; generated loop code\n" +
        loopLabel + ":\n" + loopCode +
        "  jmp " + loopLabel;

    Blockly.asm.finish();
    //assemblyCode = Blockly.asm.workspaceToCode(workspace);
    let assembledData = assemble(assemblyCode);
    console.log(assembledData.percentage);
    hexFile = assembledData.hex;
}
workspace.addChangeListener(myUpdateFunction);


createNumber = function(button)
{
    workspace.createVariable(prompt("Variable name:", "num"),"Number",null);
}

createBoolean = function(button)
{
    workspace.createVariable(prompt("Variable name:", "bool"),"Boolean",null);
}

// set callback functions
workspace.registerButtonCallback('BUTTON_CREATE_NUMBER', createNumber);
workspace.registerButtonCallback('BUTTON_CREATE_BOOLEAN', createBoolean);
        

function OpenRightSideBar(a) {//768
void 0 == a && (a = 500, a > window.screen.availWidth / 2 && (a = window.screen.availWidth / 2));
var b = $(window).width(),
    b = b - a,
    b = 0 > b ? "0" : "" + b;
$("#blocklyDiv").animate({
    width: b
}, {
    duration: 750,
    step: function() {
        //$(window).resize();
        //onresize();
        Blockly.svgResize(workspace);
    },
    done: function() {
        Blockly.svgResize(workspace);
        $("#blocklyDiv").css("width", "calc(100% - " + a + "px)")
    }
})
};

function CloseRightSidebar(a) {
$("#blocklyDiv").animate({
    width: "100%"
}, {
    duration: 750,
    step: function() {
        //$(window).resize();
        //onresize();
        Blockly.svgResize(workspace);
    },
    done: function() {
        $(window).resize();
        $(a).removeClass("right_active");
        Blockly.svgResize(workspace);
    }
})
};


var isOut = false;

$("#help_button").click(function() {
if(isOut){
    
    CloseRightSidebar("#side_bar");
}
else {
    $("#side_bar").addClass("right_active");
    OpenRightSideBar(500);
}
isOut = !isOut;
});

//$("#help_button").click(function() {
//	var percentage = "70%"
//	if(isOut){
//		percentage = "0%"
//	}
//	$("#help_text").animate({
//		height: percentage
//		step: function() {
//		}
//	}, 1000, function() {
//		// Animation complete.
//	});
//	isOut = !isOut;
//});

SetActivePage = function(a) {
$(".selectedHelp").removeClass("selectedHelp");
$("#" + a).addClass("selectedHelp");
$("#helpContent").scrollTo("#" + a, 300, {
    offset: {
        left: 0,
        top: -20
    },
    axis: "y"
})
};

function onBlockSelected(event) {
  if (event.type == Blockly.Events.UI && event.element == 'selected' && isOut) {

    var selectedBlock = Blockly.selected;

    if(selectedBlock != null)
    {
      //workspace.removeChangeListener(onFirstComment);
      $(".block_info_selected").removeClass("block_info_selected");
      $("#" + selectedBlock.type).addClass("block_info_selected");

      var container = $("#side_bar");
      var scroll_target = $('#'+selectedBlock.type);
      if(scroll_target.offset() != undefined && container.offset() != undefined)
      {
        container.animate({
            scrollTop: (scroll_target.offset().top - container.offset().top + container.scrollTop() - 20)
        },200);
      }
    }
  }
}
workspace.addChangeListener(onBlockSelected);



// initalize the language selector
LangHandler.initLanguage();




// download file via browser
downloadFile = function(filename, data) {
    var blob = new Blob([data], {type: 'text/csv'});
    {
            var elem = window.document.createElement('a');
            elem.href = window.URL.createObjectURL(blob);
            elem.download = filename;        
            document.body.appendChild(elem);
            elem.click();        
            document.body.removeChild(elem);
    }
}


// save and load
function downloadSaveFile()
{
	var xml = Blockly.Xml.workspaceToDom(workspace);
	var xml_text = Blockly.Xml.domToText(xml);
	downloadFile('program.xml', xml_text);
}


function loadSaveFile()
{
	document.getElementById("loadFileSelector").click();
}


function onSaveFileLoaded()
{
	var file = document.getElementById("loadFileSelector").files[0];
	
	if(file != null)
	{
		var fr = new FileReader();
		fr.readAsText(file, "UTF-8");
		fr.onload = function(evt)
		{
			workspace.clear();
			var xml = Blockly.Xml.textToDom(evt.target.result);
			Blockly.Xml.domToWorkspace(xml, workspace);
		}
	}
}


function runProgram()
{
	myUpdateFunction();
    let xmlHttp = new XMLHttpRequest();
    //xmlHttp.onreadystatechange = httpPostProcessRequest;
    let formData = new FormData();
    formData.append("hexFile", new Blob([hexFile], { type: "text/plain"}), "program.hex");
    xmlHttp.open("POST", "/edit");
    xmlHttp.send(formData);
}



function post(path, params, method) {
    method = method || "post"; // Set method to post by default if not specified.

    // The rest of this code assumes you are not using a library.
    // It can be made less wordy if you use one.
    var form = document.createElement("form");
    form.setAttribute("method", method);
    form.setAttribute("action", path);

    for(var key in params) {
        if(params.hasOwnProperty(key)) {
            var hiddenField = document.createElement("input");
            hiddenField.setAttribute("type", "hidden");
            hiddenField.setAttribute("name", key);
            hiddenField.setAttribute("value", params[key]);

            form.appendChild(hiddenField);
        }
    }

    document.body.appendChild(form);
    form.submit();
}