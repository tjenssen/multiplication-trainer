//// main.qml
//
// untested chatgpt result:

//import QtQuick 2.0
//import "game.js" as GameLogic
//
//Item {
//    // Verwendung von Funktionen aus game.js
//    Component.onCompleted: {
//        var task = GameLogic.createMultiplicationTask(7, 7);
//        console.log(task.question); // "7 x 7"
//        // Weitere Logik...
//    }
//}


function shuffleArray(array) {
    let currentIndex = array.length, temporaryValue, randomIndex;
    while (0 !== currentIndex) {
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex -= 1;
        temporaryValue = array[currentIndex];
        array[currentIndex] = array[randomIndex];
        array[randomIndex] = temporaryValue;
    }
    return array;
}

function similarButWrongAnswer(answer) {
    let similarAnswer;
    do {
        let chars = answer.split("");
        chars = shuffleArray(chars);
        similarAnswer = chars.join("");
    } while (similarAnswer === answer);
    return similarAnswer;
}

function randomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function createMultiplicationTask(x, y) {
    let task = { question: x + " x " + y, answer: (x * y).toString(), possibleAnswers: [] };
    if (task.answer.length > 1) {
        task.possibleAnswers.push(similarButWrongAnswer(task.answer));
    }
    while (task.possibleAnswers.length < 3) {
        let possibleAnswer = (randomNumber(1, 9) * randomNumber(1, 9)).toString();
        if (task.possibleAnswers.indexOf(possibleAnswer) === -1 && possibleAnswer !== task.answer && possibleAnswer.length === 2) {
            task.possibleAnswers.push(possibleAnswer);
        }
    }
    return task;
}

// TODO: maybe this is not necessary -> https://doc.qt.io/qt-6/qtqml-javascript-resources.html
// Exportieren der Funktionen, damit sie in QML verfügbar sind
module.exports = {
    createMultiplicationTask: createMultiplicationTask,
    similarButWrongAnswer: similarButWrongAnswer,
    shuffleArray: shuffleArray,
    randomNumber: randomNumber
};
