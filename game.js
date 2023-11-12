// vielleicht wäre das mal was für testdriven
// https://jestjs.io/docs/getting-started
// bzw. hier ein alter blog beitrag https://www.codecentric.de/wissens-hub/blog/javascript-unit-tests-sind-schwer-aufzusetzen-keep-calm-use-jest

// untested chatgpt result:

//// main.qml
//
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


// game.js

var tasks = []; // An array to hold tasks
var currentTaskIndex = 0;
var score = 0;
var remainingTime = 0; // in seconds
var taskIntervalTime = 10; // in seconds
var isInCheckAnswer = false;

function setTasks(newTasks) {
    tasks = newTasks;
}

function reset() {
    currentTaskIndex = 0;
    score = 0;
    remainingTime = 0;
    isInCheckAnswer = false;
    // Initialize other properties and states as needed
}

function nextTask() {
    if (currentTaskIndex < tasks.length - 1) {
        currentTaskIndex++;
    } else {
        // Handle end of tasks list
    }
}

function checkAnswer(answer) {
    if (tasks[currentTaskIndex].answer === answer) {
        score += tasks[currentTaskIndex].score;
        nextTask();
    } else {
        // Handle wrong answer
    }
}

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
    setTasks: setTasks,
    reset: reset,
    nextTask: nextTask,
    checkAnswer: checkAnswer,
    tasks: tasks,
    currentTaskIndex: currentTaskIndex,
    score: score,
    remainingTime: remainingTime,
    taskIntervalTime: taskIntervalTime,
    isInCheckAnswer: isInCheckAnswer
};
