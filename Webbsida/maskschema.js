function loadEvent(fn) {
	var oldonload = window.onload;
	if (typeof window.onload != 'function') {
		window.onload = fn;
	}
	else {
		window.onload = function() {
			oldonload();
			fn();
		}
	}
}

var regEvent=(function(){
	var elem=document.createElement('div');
	if(elem.addEventListener){
		return function(elem, eventName, fn){
			elem.addEventListener(eventName, fn, false);
		}
	}
	else if(elem.attachEvent){
		return function(elem, eventName, fn){
			elem.attachEvent('on'+eventName, fn);
		}
	}
})();

function addEvent(elem, eventName, fn){
	var cb=(function(){
		return function(event){
			fn.call(this, normaliseEvent(event || window.event));
		}
	})();
	regEvent(elem, eventName, cb);
}

function normaliseEvent(event) {
	if (!event.stopPropagation) {
		event.stopPropagation = function() {this.cancelBubble = true;};
		event.preventDefault = function() {this.returnValue = false;};
	}
	if (!event.stop) {
		event.stop = function() {
			this.stopPropagation();
			this.preventDefault();
		};
	}
	if (event.srcElement && !event.target) {
			event.target = event.srcElement;
	}
	return event;
}

loadEvent(function(){
	var steps = [];
	function addStep(temp, time){
		document.getElementById('steps').innerHTML = "";
		steps.push([temp,time]);
		for(var i = 0; i < steps.length; i++){
			var newParagraph = document.createElement('p');
			newParagraph.textContent = "Steg " + (i+1) + " Måltemperatur: " + steps[i][0] + " C  Längd: " + steps[i][1] + " Min";
			document.getElementById('steps').appendChild(newParagraph);
		}
	}

	function saveScheme(){
		alert("test");
		
	}

	function checkName(free){
		if(free == "success"){
			document.getElementById('name').style.backgroundColor = "white";
			alert("Namnet är ledigt");
			if(steps){
				var XHR = new XMLHttpRequest();
				XHR.onreadystatechange = function(){
					if (XHR.readyState == 4 && XHR.status == 200) {
		                alert(XHR.responseText);
		            }
		        }
		        XHR.open("GET", "sqlfunctions.php?type=saveSchedule&name="+document.getElementById('name').value+"&array="+JSON.stringify(steps), true);
		        XHR.send();
	    	}
		}
		else{
			alert("Namnet är upptaget");
			document.getElementById('name').style.backgroundColor = "#FF4D4D";
			document.getElementById('name').focus();
		}
	}
	
	function validateName(name){
		if(name.value != ""){
			
			var XHR = new XMLHttpRequest();
			XHR.onreadystatechange = function(){
				if (XHR.readyState == 4 && XHR.status == 200) {
					checkName(XHR.responseText);
				}
			};
			XHR.open("GET", "sqlfunctions.php?type=checkName&name="+name.value, true);
			XHR.send();
		}
		else{
			name.style.backgroundColor = "#FF4D4D";
			name.focus();
			return false;
		}
		//Läs in från databasen om namnet finns eller ej.
	}
	
	function validateTemp(temp){
		if(temp.value != ""){
			if(/^\d+$/.test(temp.value) && temp.value > 0 && temp.value <= 100){
				temp.style.backgroundColor = "white";
				return true;
			}
			else{
				temp.focus();
				temp.style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
			temp.focus();
			temp.style.backgroundColor = "#FF4D4D";
			return false;
		}
		//Kolla så det är siffror och så det är mellan 0 och 100
	}
	
	function validateTime(time){
		if(time.value != ""){
			if(/^\d+$/.test(time.value) && time.value > 0){
				time.style.backgroundColor = "white";
				return true;
			}
			else{
				time.focus();
				time.style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
			time.focus();
			time.style.backgroundColor = "#FF4D4D";
			return false;
		}
		//Kolla så det är siffror. Fråga om det överstiger 2 timmar.
	}
	
	addEvent(document.getElementById('temp'), 'keypress', function(e){
		if(e.keyCode == 13){
			e.preventDefault();
			document.getElementById('time').focus();
		}
	});

	addEvent(document.getElementById('addStepForm'),'submit',function(e){
		e.preventDefault();
		if(validateTemp(document.getElementById('temp'))){
			if(validateTime(document.getElementById('time'))){
				addStep(document.getElementById('temp').value, document.getElementById('time').value);
				document.getElementById('temp').value = "";
				document.getElementById('temp').focus();
				document.getElementById('time').value = "";
			}
		}
	});
	
	addEvent(document.getElementById('saveScheme'), 'click', function(e){
		validateName(document.getElementById('name'));
	});

	addEvent(document.getElementById('openScheme'), 'click', function(e){
		var XHR = new XMLHttpRequest();
		XHR.onreadystatechange = function(){
			if (XHR.readyState == 4 && XHR.status == 200) {
                alert(XHR.responseText);
            }
        }
        XHR.open("GET", "openScheme", true);
        XHR.send();
	});
	
});