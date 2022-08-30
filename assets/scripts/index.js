console.log('hello')

$(function () {
    console.log('world')
})


const inputElement = document.querySelector('input[type="text"]');
const log = document.querySelector('.event-log-contents');
const clearLog = document.querySelector('.clear-log');

clearLog.addEventListener('click', () => {
    log.textContent = '';
});

function handleEvent(event) {
    log.textContent = log.textContent + `${event.type}: ${event.data}\n`;
    var type = String(event.type)
    var data = String(event.data)
    window.moduleConfig.callComposition(type, data)
}

inputElement.addEventListener('compositionstart', handleEvent);
inputElement.addEventListener('compositionupdate', handleEvent);
inputElement.addEventListener('compositionend', handleEvent);