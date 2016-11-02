var lineWidth = 2; // the width of idle line.
var seperatorWidth = 1; // the width of white lines at each time tag points.
var seperatorDistance = 100;
var bigBoxWidth = 30; // the vertical length of box.
var smallBoxWidth = 20;
var innerBoxWidthRatio = 0.4; // in a two color box, width(innerBox) = 0.4 * width(outerBox).
var cpuLineMargin = 50; // the blank spaces between two cpu lines.
var maxLength = 2000;
var lineheight=2;
var horizontalpadding=100;


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

var events_1=[[0,1300,1500,200,46,"hjds"],[0,1300,1500,200,46,"hjds"],[0,1300,1500,200,46,"hjds"]]

var content = "<svg style=\"width:" + maxLength + "; height:" + (bigBoxWidth + cpuLineMargin) * 5 + "\">";
var events0 = [[0,100,100,"line"],[100,100,50,"smallBox"],[150,100,100,"line"],[250,100,2,"line"],[252,100,8,"smallBox"], [260,100,40,"bigBox"], [300, 100,50,"line"],[350,100,100,"smallBox"],[450,100,50,"bigBox"],[500,100,50,"line"]]
var events1 = [[1,100,0,100,"lline"],[0,200,0,30,"linde"],[1,250,0,100,"lihne"],[1,350,0,30,"lihne"],[1,380,0,100,"lines"]]
var events0 = [[0,100,0,10,"lines"],[0,200,0,30,"lihne"],[0,250,0,100,"linhe"],[0,350,0,30,"lkne"],[0,380,0,100,"lines"]]
//,[252,100,8,"smallBox"], [260,100,40,"bigBox"], [300, 100,50,"line"],[350,100,100,"smallBox"],[450,100,50,"bigBox"],[500,100,50,"line"]]

events0=processCoordinates(events0);
events1=processCoordinates(events1);

line0=events0[0];
//line0[1]=horizontalpadding;
//line0[3]=events0[events0.length-1][1];
content+=drawLine(line0[1],line0[2]+20,events0[events0.length-2][1],lineheight);

line1=events1[0];
//line1[1]=horizontalpadding;
//line1[3]=events1[events1.length-1][1];
content+=drawLine(line1[1],line1[2]+20,events1[events1.length-2][1],lineheight);


//var events1 = [[0,50,"line"],[50,150,"smallBox"],[150,250,"bigBox"],[250,252,"line"],[252,278,"smallBox"], [278, 300, "bigBox"], [300, 350, "line"],[350,450,"smallBox"],[450,452,"bigBox"],[452,466,"line"],[466,468,"bigBox"],[468,1252,"line"]]
//var events2 = [[0,200,"line"],[200,250,"bigBox"],[250,252,"line"],[252,283,"smallBox"], [283, 300, "bigBox"], [300, 340, "line"],[340,440,"smallBox"],[440,550,"bigBox"],[550,1150,"smallBox"],[1150,1252,"line"]]
//var events3 = [[0,1000,"line"],[1000,1150,"bigBox"],[1150,1252,"line"]]
// Draw the CPU 0

for (i = 0; i < events0.length; i++) {
    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
	content += appendEvent(events0[i]);
}
for (i = 0; i < events1.length; i++) {
    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
	content += appendEvent(events1[i]);
}
//for (i = 0; i < events1.length; i++) {
    // Append a event at the end of CPU 0, vertical position offset = 0 * one line.
//	content += appendEvent(events1[i]);
//}

// Draw the CPU 1
// for (i = 0; i < events1.length; i++) {
//     // Append an event at the end of CPU 1, vertical position offset = 1 * one line.
// 	content += appendEvent(events1[i][0], events1[i][1], events1[i][2], bigBoxWidth + cpuLineMargin);
// }
// // Draw the CPU 2
// for (i = 0; i < events2.length; i++) {
//     // Append an event at the end of CPU 2, vertical position offset = 2 * one line.
// 	content += appendEvent(events2[i][0], events2[i][1], events2[i][2], 2 * (bigBoxWidth + cpuLineMargin));
// }
// // Draw the CPU 3
// for (i = 0; i < events3.length; i++) {
//     // Append an event at the end of CPU 3, vertical position offset = 3 * one line.
// 	content += appendEvent(events3[i][0], events3[i][1], events3[i][2], 3 * (bigBoxWidth + cpuLineMargin));
//}
// Draw the vertical white time tag line.
for (i = 0; i < maxLength; i += seperatorDistance)
	content += drawTicks(i, 100, seperatorWidth,40);
content += "</svg>"; 
document.getElementById("plotSVG").innerHTML = content;