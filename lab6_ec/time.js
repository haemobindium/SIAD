<script>
function startTime(){
document.getElementById('clock')..innerHTML=new Date();
setTimeout(startTime,500);
}
</script>
<body onload="startTime()">
<div id="clock"></div>

