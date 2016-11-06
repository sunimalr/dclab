var lineWidth = 2; // the width of idle line.
var seperatorWidth = 2; // the width of white lines at each time tag points.

var bigBoxWidth = 30; // the vertical length of box.
var smallBoxWidth = 20;
var innerBoxWidthRatio = 0.4; // in a two color box, width(innerBox) = 0.4 * width(outerBox).
var cpuLineMargin = 50; // the blank spaces between two cpu lines.
var maxLength = 8000000;
var maxHeight = 3000;
var lineheight=2;
var horizontalpadding=200;
var hundredNanotoPixel= 0.01;
var seperatorDistance = hundredNanotoPixel*10000;
var startTime=0;
var textHeight=20;
var legend = {};

//100 nanosecond = 5 pixels

// Generate a event box. offsetTop is added to the vertical absolute position of the box.
function appendEvent(event) {
	var height = 0, color = "black", verticalPosition = 0;
	var type = event[4];
	if (type == "line") {
	}
	else {
		if((event[5]!="poll")&&(event[5]!="select")&&event[3]>0 && event[1]<startTime){
			return drawRectangle(event[1],event[2],event[3],event[4],event[5]);
		}
	}
}

function plot(entries){
	
	var content = "<svg style=\"width:" + maxLength + "; height:" + maxHeight + "\">";
	
	var events = [];
	for (key in entries) {
		console.log(key);
		var temp=(generateCoordinates(entries[key]));
		events.push(processCoordinates(temp));
	}

	var line = [];
	var finalpoint;
	for (key in entries) {
		line[key]=events[key][0];
		maxLength=events[key][events[key].length-2][1];
		finalpoint=((maximumStart-minimumStart)/100)*hundredNanotoPixel;
		//content+=drawLine(line[key][1],line[key][2]+20,events[key][events[key].length-2][1],lineheight);
		content+=drawLine(horizontalpadding,line[key][2]+20,finalpoint,lineheight);
		console.log("finalpoint : "+finalpoint+" old: "+events[key][events[key].length-2][1]);
	}

	for (key in entries) {
		for (i = 0; i < events[key].length; i++) {
	    	// Append a event at the end of CPU 0, vertical position offset = 0 * one line.
			content += appendEvent(events[key][i]);
			var textposition=125+key*100;
			//console.log(textposition);
			var textcontent= "<text x=\"60\" y=\""+textposition+"\" font-size=\"20px\"> CPU " + key + "</text>" //"<text x=\"20\" y=\"20\" font-family=\"sans-serif\" font-size=\"20px\" fill=\"black\">CPU" + key "</text>";
			content+="<svg width=\"150\" height=\"1000\">" + textcontent +" </svg>"			
		}		
	}

	// Draw the vertical white time tag line.
	for (i = horizontalpadding; i < finalpoint; i += seperatorDistance){
		content += drawTicks(i, 100, seperatorWidth,40);
		content += "<text x=\"" + i + "\" y=\"" + 90 + "\" font-size=\"10px\" fill=\"black\">" + i/seperatorDistance + "ms</text>";
	}
		
	for (i = horizontalpadding; i < finalpoint; i += seperatorDistance)
		content += drawTicks(i, 200, seperatorWidth,40);
	for (i = horizontalpadding; i < finalpoint; i += seperatorDistance)
		content += drawTicks(i, 300, seperatorWidth,40);
	for (i = horizontalpadding; i < finalpoint; i += seperatorDistance)
		content += drawTicks(i, 400, seperatorWidth,40);

	//Draw legend

	for (eventName in legend){
		content+=legend[eventName];
		console.log(eventName);
	}

	content += "</svg>"; 
	document.getElementById("plotSVG").innerHTML = content;
}

function handleFileSelect(evt){

	var reader = new FileReader();
	reader.onload = function(e) {
		//fileDisplayArea.innerText = reader.result;
	    var lines = this.result.split('\n');
	    entries = parseTrace(lines);
	    //console.log(entries[2][1][1]);
	    plot(entries);
	}
	reader.readAsText(evt.target.files[0]);	
	//hundredNanotoPixel=parseInt(document.getElementById('txtResolution')[0].value);	
	//console.log(hundredNanotoPixel);
}
document.getElementById('files').addEventListener('change', handleFileSelect, false);
