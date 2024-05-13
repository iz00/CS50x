// Code to check answers to questions of trivia webpage

// Wait for DOM content to load
document.addEventListener('DOMContentLoaded', function() {

    // Get the feedback paragraph and all the buttons from the multiple choice question
    let feedback_multiple_choice = document.querySelector('#feedback_multiple_choice');
    let buttons = document.querySelectorAll('button[type="button"]');

    // Iterate through all buttons from the multiple choice question, through their indexes on the array
    for (let i = 0; i < buttons.length; i++) {

        // Add event listeners for click on each of them
        buttons[i].addEventListener('click', function() {

            // Check if clicked button is the correct one
            if (buttons[i] === document.querySelector('#correct')) {

                // Set feedback to correct
                feedback_multiple_choice.innerHTML = 'Correct!';
                feedback_multiple_choice.style.color = '#00ff00'; // Green

                // Set button color to green
                buttons[i].style.backgroundColor = '#00ff7f'; // Spring green
                buttons[i].style.border = '3px solid #228b22'; // Forest green
                buttons[i].style.color = '#000'; // Black

            } else {

                // Set feedback to incorrect
                feedback_multiple_choice.innerHTML = 'Incorrect.';
                feedback_multiple_choice.style.color = '#ff0000'; // Red

                // Set button color to red
                buttons[i].style.backgroundColor = '#ff6347'; // Tomato
                buttons[i].style.border = '3px solid #8b0000'; // Dark red
                buttons[i].style.color = '#000'; // Black
            }

            // When whichever button is clicked, disable all buttons and hover effects on them
            for (button of buttons) {
                button.disabled = true;
                button.style.pointerEvents = 'none';
            }
        });
    }

    // Get the feedback paragraph and the button from the free response question
    let feedback_free_response = document.querySelector('#feedback_free_response');
    let submit_button = document.querySelector('button[type="submit"]');

    // Add event listener for click on button
    submit_button.addEventListener('click', function() {

        // Get the answer user typed, trim leading and trailing whitespaces, lower it, and check if correct
        answer = document.querySelector('input');
        if (answer.value.trim().toLowerCase() === 'switzerland') {

            // Set feedback to correct
            feedback_free_response.innerHTML = 'Correct!';
            feedback_free_response.style.color = '#00ff00'; // Green

            // Set text field color to green
            answer.style.backgroundColor = '#00ff7f'; // Spring green
            answer.style.border = '3px solid #228b22'; // Forest green
            answer.style.color = '#000'; // Black
            answer.style.textAlign = 'center';

            // Disable text field, submit button, and hover effects
            answer.disabled = true;
            submit_button.disabled = true;
            submit_button.style.pointerEvents = 'none';

        } else {

            // Set feedback to incorrect
            feedback_free_response.innerHTML = 'Incorrect.';
            feedback_free_response.style.color = '#ff0000'; // Red

            // Set text field color to red
            answer.style.backgroundColor = '#ff6347'; // Tomato
            answer.style.border = '3px solid #8b0000'; // Dark red
        }
    });
});
