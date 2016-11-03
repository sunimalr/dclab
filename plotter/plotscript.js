var lineWidth = 2; // the width of idle line.
var seperatorWidth = 1; // the width of white lines at each time tag points.

var bigBoxWidth = 30; // the vertical length of box.
var smallBoxWidth = 20;
var innerBoxWidthRatio = 0.4; // in a two color box, width(innerBox) = 0.4 * width(outerBox).
var cpuLineMargin = 50; // the blank spaces between two cpu lines.
var maxLength = 200000;
 lineheight=2;
var horizontalpadding=200;
var hundredNanotoPixel=0.01;
var seperatorDistance = hundredNanotoPixel*1000;
//100 nanosecond = 5 pixels

// Generate a event box. offsetTop is added to the vertical absolute position of the box.
function appendEvent(event) {
	var height = 0, color = "black", verticalPosition = 0;
	var type = event[4];
	if (type == "line") {
		//return drawLine(event[1],event[2]+20,event[3],lineheight); 
	}
	else {
		return drawRectangle(event[1],event[2],event[3]);
	}
}

function plot(entries){
	//var events_1=[[0,1300,1500,200,46,"hjds"],[0,1300,1500,200,46,"hjds"],[0,1300,1500,200,46,"hjds"]]
	var content = "<svg style=\"width:" + maxLength + "; height:" + (bigBoxWidth + cpuLineMargin) * 5 + "\">";
	//var events0 = [[0,100,100,"line"],[100,100,50,"smallBox"],[150,100,100,"line"],[250,100,2,"line"],[252,100,8,"smallBox"], [260,100,40,"bigBox"], [300, 100,50,"line"],[350,100,100,"smallBox"],[450,100,50,"bigBox"],[500,100,50,"line"]]
	//var events1 = [[1,100,0,100,0x45,"lline"],[0,200,0,30,0x36,"linde"],[1,250,0,100,0x23,"lihne"],[1,350,0,30,0xd,"lihne"],[1,380,0,10,0xc,"lines"]]
	//var events0 = [[0,100,0,10,0x4,"lines"],[0,200,0,30,0x23,"lihne"],[0,250,0,100,0x33,"linhe"],[0,350,0,30,0x12,"lkne"],[0,380,0,100,0x34,"lines"]]
	//,[252,100,8,"smallBox"], [260,100,40,"bigBox"], [300, 100,50,"line"],[350,100,100,"smallBox"],[450,100,50,"bigBox"],[500,100,50,"line"]]

	var events0=generateCoordinates(entries[0]);
	var events1=generateCoordinates(entries[1]);


	events0=processCoordinates(events0);
	events1=processCoordinates(events1);

	line0=events0[0];
	content+=drawLine(line0[1],line0[2]+20,events0[events0.length-2][1],lineheight);

	line1=events1[0];
	content+=drawLine(line1[1],line1[2]+20,events1[events1.length-2][1],lineheight);



	for (i = 0; i < events0.length; i++) {
	    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
		content += appendEvent(events0[i]);
	}
	for (i = 0; i < events1.length; i++) {
	    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
		content += appendEvent(events1[i]);
	}
	
	// Draw the vertical white time tag line.
	for (i = 0; i < maxLength; i += seperatorDistance)
		content += drawTicks(i, 100, seperatorWidth,40);
	for (i = 0; i < maxLength; i += seperatorDistance)
		content += drawTicks(i, 200, seperatorWidth,40);
	for (i = 0; i < maxLength; i += seperatorDistance)
		content += drawTicks(i, 300, seperatorWidth,40);
	for (i = 0; i < maxLength; i += seperatorDistance)
		content += drawTicks(i, 400, seperatorWidth,40);

	content += "</svg>"; 
	document.getElementById("plotSVG").innerHTML = content;
}

function handleFileSelect(evt){

	var reader = new FileReader();
	reader.onload = function(e) {
		//fileDisplayArea.innerText = reader.result;
	    var lines = this.result.split('\n');
	    entries = parseTrace(lines);
	    console.log(entries[2][1][1]);
	    plot(entries);
	}
	reader.readAsText(evt.target.files[0]);	
}
document.getElementById('files').addEventListener('change', handleFileSelect, false);
