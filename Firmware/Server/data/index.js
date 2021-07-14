var connection = new WebSocket('ws://' + location.hostname + '/ws', ['arduino']);

connection.onopen = function ()
{
	console.log('Connected: ');
};

connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};

connection.onmessage = function (e) {
  console.log('Server: ', e.data);
  processData(e.data);
};

connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function sendData()
{
  let ledNumber = document.getElementById('ledNumber');
  let ledStatus = document.querySelector('input[name="status"]:checked');

  let data =
	{
	  command : "Set",
	  id: ledNumber.value,
	  status: ledStatus.value
  }
  let json = JSON.stringify(data);

  connection.send(json);
}

function getData()
{
  let data =
	{
	  command : "Get"
  }
  let json = JSON.stringify(data);
  connection.send(json);
}
function setColor(jsonData)
{
	let circleColor = 'black';
	switch(jsonData)
	{
	    case 0:
	        circleColor = 'black';
	        break;
	    case 1:
	        circleColor = 'blue';
	        break;
	    case 2:
	        circleColor = 'red';
	        break;
			case 3:
					circleColor = 'green';
					break;
	    default:
	        circleColor = 'black';
					break;
	}
	return circleColor;
}

function processData(data)
{
  let json = JSON.parse(data);
  console.log(json);

	document.getElementById("circle00").style.background = setColor(json.id00);
	document.getElementById("circle01").style.background = setColor(json.id01);
	document.getElementById("circle02").style.background = setColor(json.id02);
	document.getElementById("circle03").style.background = setColor(json.id03);
	document.getElementById("circle04").style.background = setColor(json.id04);
	document.getElementById("circle05").style.background = setColor(json.id05);
	document.getElementById("circle06").style.background = setColor(json.id06);
	document.getElementById("circle07").style.background = setColor(json.id07);
	document.getElementById("circle08").style.background = setColor(json.id08);
	document.getElementById("circle09").style.background = setColor(json.id09);

	document.getElementById("circle10").style.background = setColor(json.id10);
	document.getElementById("circle11").style.background = setColor(json.id11);
	document.getElementById("circle12").style.background = setColor(json.id12);
	document.getElementById("circle13").style.background = setColor(json.id13);
	document.getElementById("circle14").style.background = setColor(json.id14);
	document.getElementById("circle15").style.background = setColor(json.id15);
	document.getElementById("circle16").style.background = setColor(json.id16);
	document.getElementById("circle17").style.background = setColor(json.id17);
	document.getElementById("circle18").style.background = setColor(json.id18);
	document.getElementById("circle19").style.background = setColor(json.id19);

	document.getElementById("circle20").style.background = setColor(json.id20);
	document.getElementById("circle21").style.background = setColor(json.id21);
	document.getElementById("circle22").style.background = setColor(json.id22);
	document.getElementById("circle23").style.background = setColor(json.id23);
	document.getElementById("circle24").style.background = setColor(json.id24);
	document.getElementById("circle25").style.background = setColor(json.id25);
	document.getElementById("circle26").style.background = setColor(json.id26);
	document.getElementById("circle27").style.background = setColor(json.id27);
	document.getElementById("circle28").style.background = setColor(json.id28);
	document.getElementById("circle29").style.background = setColor(json.id29);

	document.getElementById("circle30").style.background = setColor(json.id30);
	document.getElementById("circle31").style.background = setColor(json.id31);
	document.getElementById("circle32").style.background = setColor(json.id32);
	document.getElementById("circle33").style.background = setColor(json.id33);
	document.getElementById("circle34").style.background = setColor(json.id34);
	document.getElementById("circle35").style.background = setColor(json.id35);
	document.getElementById("circle36").style.background = setColor(json.id36);
	document.getElementById("circle37").style.background = setColor(json.id37);
	document.getElementById("circle38").style.background = setColor(json.id38);
	document.getElementById("circle39").style.background = setColor(json.id39);

	document.getElementById("circle40").style.background = setColor(json.id40);
	document.getElementById("circle41").style.background = setColor(json.id41);
	document.getElementById("circle42").style.background = setColor(json.id42);
	document.getElementById("circle43").style.background = setColor(json.id43);
	document.getElementById("circle44").style.background = setColor(json.id44);
	document.getElementById("circle45").style.background = setColor(json.id45);
	document.getElementById("circle46").style.background = setColor(json.id46);
	document.getElementById("circle47").style.background = setColor(json.id47);
	document.getElementById("circle48").style.background = setColor(json.id48);
	document.getElementById("circle49").style.background = setColor(json.id49);

	document.getElementById("circle50").style.background = setColor(json.id50);
	document.getElementById("circle51").style.background = setColor(json.id51);
	document.getElementById("circle52").style.background = setColor(json.id52);
	document.getElementById("circle53").style.background = setColor(json.id53);
	document.getElementById("circle54").style.background = setColor(json.id54);
	document.getElementById("circle55").style.background = setColor(json.id55);
	document.getElementById("circle56").style.background = setColor(json.id56);
	document.getElementById("circle57").style.background = setColor(json.id57);
	document.getElementById("circle58").style.background = setColor(json.id58);
	document.getElementById("circle59").style.background = setColor(json.id59);

	document.getElementById("circle60").style.background = setColor(json.id60);
	document.getElementById("circle61").style.background = setColor(json.id61);
	document.getElementById("circle62").style.background = setColor(json.id62);
	document.getElementById("circle63").style.background = setColor(json.id63);
	document.getElementById("circle64").style.background = setColor(json.id64);
	document.getElementById("circle65").style.background = setColor(json.id65);
	document.getElementById("circle66").style.background = setColor(json.id66);
	document.getElementById("circle67").style.background = setColor(json.id67);
	document.getElementById("circle68").style.background = setColor(json.id68);
	document.getElementById("circle69").style.background = setColor(json.id69);

	document.getElementById("circle70").style.background = setColor(json.id70);
	document.getElementById("circle71").style.background = setColor(json.id71);
	document.getElementById("circle72").style.background = setColor(json.id72);
	document.getElementById("circle73").style.background = setColor(json.id73);
	document.getElementById("circle74").style.background = setColor(json.id74);
	document.getElementById("circle75").style.background = setColor(json.id75);
	document.getElementById("circle76").style.background = setColor(json.id76);
	document.getElementById("circle77").style.background = setColor(json.id77);
	document.getElementById("circle78").style.background = setColor(json.id78);
	document.getElementById("circle79").style.background = setColor(json.id79);

	document.getElementById("circle80").style.background = setColor(json.id80);
	document.getElementById("circle81").style.background = setColor(json.id81);
	document.getElementById("circle82").style.background = setColor(json.id82);
	document.getElementById("circle83").style.background = setColor(json.id83);
	document.getElementById("circle84").style.background = setColor(json.id84);
	document.getElementById("circle85").style.background = setColor(json.id85);
	document.getElementById("circle86").style.background = setColor(json.id86);
	document.getElementById("circle87").style.background = setColor(json.id87);
	document.getElementById("circle88").style.background = setColor(json.id88);
	document.getElementById("circle89").style.background = setColor(json.id89);

	document.getElementById("circle90").style.background = setColor(json.id90);
	document.getElementById("circle91").style.background = setColor(json.id91);
	document.getElementById("circle92").style.background = setColor(json.id92);
	document.getElementById("circle93").style.background = setColor(json.id93);
	document.getElementById("circle94").style.background = setColor(json.id94);
	document.getElementById("circle95").style.background = setColor(json.id95);
	document.getElementById("circle96").style.background = setColor(json.id96);
	document.getElementById("circle97").style.background = setColor(json.id97);
	document.getElementById("circle98").style.background = setColor(json.id98);
	document.getElementById("circle99").style.background = setColor(json.id99);

}
