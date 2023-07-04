<!DOCTYPE html>
<html>
<head>
  <title>Print Digits Example</title>
</head>
<body>
  <label for="numberInput">Enter a number:</label>
  <input type="number" id="numberInput">
  <button onclick="printDigits()">Print Digits</button>
  <div id="result"></div>

  <script>
    function printDigits() {
      // Retrieve the input element
      var input = document.getElementById("numberInput");
      
      // Retrieve the entered value
      var number = input.value;
      
      // Convert the number to a string
      var numberString = number.toString();
      
      // Create a new HTML element for each digit
      var resultDiv = document.getElementById("result");
      resultDiv.innerHTML = ""; // Clear previous content
      
      for (var i = 0; i < numberString.length; i++) {
        var digitElement = document.createElement("p");
        digitElement.innerText = numberString.charAt(i);
        resultDiv.appendChild(digitElement);
      }
    }
  </script>
</body>
</html>
