var lineWidth = 2; // the width of idle line.
var seperatorWidth = 1; // the width of white lines at each time tag points.
var seperatorDistance = 70;
var bigBoxWidth = 30; // the vertical length of box.
var smallBoxWidth = 20;
var innerBoxWidthRatio = 0.4; // in a two color box, width(innerBox) = 0.4 * width(outerBox).
var cpuLineMargin = 50; // the blank spaces between two cpu lines.
var maxLength = 2000;


// Generate a event box. offsetTop is added to the vertical absolute position of the box.
function appendEvent(startTime, endTime, type, offsetTop) {
	var height = 0, color = "black", verticalPosition = 0;
	if (type == "line") {
		height = lineWidth;
		verticalPosition = (bigBoxWidth - lineWidth) / 2;
		color = "black"; 
	}
	else if (type == "smallBox") {
		height = smallBoxWidth;
		verticalPosition = (bigBoxWidth - smallBoxWidth) / 2;
		color = "blue";
	}
	else if (type == "bigBox") {
		height = bigBoxWidth;
		verticalPosition = 0;
		color = "red";
	}
	return drawRectangle(startTime, offsetTop + verticalPosition, endTime - startTime, height, color);
}
var content = "<svg style=\"width:" + maxLength + "; height:" + (bigBoxWidth + cpuLineMargin) * 5 + "\">";
var events0 = [[0,100,"line"],[100,150,"smallBox"],[150,250,"bigBox"],[250,252,"line"],[252,278,"smallBox"], [278, 300, "bigBox"], [300, 350, "line"],[350,450,"smallBox"],[450,1150,"bigBox"],[1150,1252,"line"]]
var events1 = [[0,50,"line"],[50,150,"smallBox"],[150,250,"bigBox"],[250,252,"line"],[252,278,"smallBox"], [278, 300, "bigBox"], [300, 350, "line"],[350,450,"smallBox"],[450,452,"bigBox"],[452,466,"line"],[466,468,"bigBox"],[468,1252,"line"]]
var events2 = [[0,200,"line"],[200,250,"bigBox"],[250,252,"line"],[252,283,"smallBox"], [283, 300, "bigBox"], [300, 340, "line"],[340,440,"smallBox"],[440,550,"bigBox"],[550,1150,"smallBox"],[1150,1252,"line"]]
var events3 = [[0,1000,"line"],[1000,1150,"bigBox"],[1150,1252,"line"]]
// Draw the CPU 0
for (i = 0; i < events0.length; i++) {
    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
	content += appendEvent(events0[i][0], events0[i][1], events0[i][2], 0);
}
// Draw the CPU 1
for (i = 0; i < events1.length; i++) {
    // Append an event at the end of CPU 1, vertical position offset = 1 * one line.
	content += appendEvent(events1[i][0], events1[i][1], events1[i][2], bigBoxWidth + cpuLineMargin);
}
// Draw the CPU 2
for (i = 0; i < events2.length; i++) {
    // Append an event at the end of CPU 2, vertical position offset = 2 * one line.
	content += appendEvent(events2[i][0], events2[i][1], events2[i][2], 2 * (bigBoxWidth + cpuLineMargin));
}
// Draw the CPU 3
for (i = 0; i < events3.length; i++) {
    // Append an event at the end of CPU 3, vertical position offset = 3 * one line.
	content += appendEvent(events3[i][0], events3[i][1], events3[i][2], 3 * (bigBoxWidth + cpuLineMargin));
}
// Draw the vertical white time tag line.
for (i = seperatorDistance; i < maxLength; i += seperatorDistance)
	content += drawRectangle(i, 0, seperatorWidth, (bigBoxWidth + cpuLineMargin) * 4,"white");
content += "</svg>"; 
document.getElementById("plotSVG").innerHTML = content;