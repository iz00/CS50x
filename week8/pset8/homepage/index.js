// Code to greet user after they submit their name on my webpage introducing myself

// Wait for DOM content to load
document.addEventListener('DOMContentLoaded', function() {

    // Add event listener for submit of form querying for name
    document.querySelector('form').addEventListener('submit', function(e) {

        // Get the input element
        let input = document.querySelector('input');

        // Set the greeting to nothing, so that the actual greeting will be printed
        document.querySelector('#greeting').innerHTML = '';

        // Set the greeting to the name the user typed in input
        let greeting = "Hello " + input.value + ", I'm Isadora.";
        let len = greeting.length,
            i = 0;

        // Function to simulate a type writer
        function type_writer() {
            // While the answer is not complete
            if (i < len) {
                // Print the greeting on the page, one character at a time
                document.querySelector('#greeting').innerHTML += greeting.charAt(i);
                i++;
                // Function will be called at an interval of 50 ms
                setTimeout(type_writer, 50);
            }
        }

        type_writer();

        // Set h2 and h3 to corresponding texts
        document.querySelector('h2').innerHTML = 'Welcome to my homepage!';
        document.querySelector('h3').innerHTML = 'Feel free to take a look around.';

        // Set the input box's new style and disable it
        input.style.backgroundColor = '#90ee90'; // Light green
        input.style.color = '#000'; // Black
        input.style.fontWeight = 'bold';
        input.disabled = true;

        // Prevent the default for submitting a form (don't change the url)
        e.preventDefault();
    });
});
