console.log('hello')

$(function () {
    console.log('world')
})


const inputElement = document.getElementById("example")
const log = document.querySelector('.event-log-contents');
const clearLog = document.querySelector('.clear-log');

clearLog.addEventListener('click', () => {
    log.textContent = '';
});

function handleEvent(event) {
    console.debug('handleComposition: ', event.type, event.data)
    log.textContent = log.textContent + `${event.type}: ${event.data}\n`;
    var type = String(event.type)
    var data = String(event.data)
    window.moduleConfig.callCompositionText(type, data)
}

inputElement.addEventListener('compositionstart', handleEvent);
inputElement.addEventListener('compositionupdate', handleEvent);
inputElement.addEventListener('compositionend', handleEvent);

function handleInput(event) {
    console.debug('handleInput: ', event.inputType, event.data)
    if (event.isComposing)
        return
    var inputType = event.inputType
    if (inputType === 'deleteContentBackward') {
        window.moduleConfig.deleteContent()
        return;
    }
    if (inputType === 'insertLineBreak' || (inputType === 'insertText' && !event.data)) {
        window.moduleConfig.insertLineBreak()
        return;
    }
    var data = String(event.data)
    window.moduleConfig.callAppendText(data)
}

inputElement.addEventListener('input', handleInput);