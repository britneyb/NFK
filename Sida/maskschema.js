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
	
	function validateName(name){
		//Läs in från databasen om namnet finns eller ej.
	}
	
	function validateTemp(temp){
		if(temp.value != ""){
			if(/^\d+$/.test(temp.value) && temp.value > 0 && temp.value <= 100){
				document.getElementById('temp').style.backgroundColor = "white";
				return true;
			}
			else{
				temp.focus();
				document.getElementById('temp').style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
			temp.focus();
			document.getElementById('temp').style.backgroundColor = "#FF4D4D";
			return false;
		}
		//Kolla så det är siffror och så det är mellan 0 och 100
	}
	
	function validateTime(time){
		if(time.value != ""){
			if(/^\d+$/.test(time.value) && time.value > 0){
				document.getElementById('time').style.backgroundColor = "white";
				return true;
			}
			else{
				time.focus();
				document.getElementById('temp').style.backgroundColor = "#FF4D4D";
				return false;
			}
		}
		else{
				time.focus();
				document.getElementById('temp').style.backgroundColor = "#FF4D4D";
				return false;
		}
		//Kolla så det är siffror. Fråga om det överstiger 2 timmar.
	}
	
	addEvent(document.getElementById('addStepForm'),'submit',function(e){
		e.preventDefault();
		if(validateTemp(document.getElementById('temp'))){
			if(validateTime(document.getElementById('time'))){
				alert("Allt Korrekt");
			}
		}
		
	});
	
});