<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $numProcesses = $_POST["numProcesses"];
    $algorithm = $_POST["algorithm"];
    $timeQuantum = $_POST["timeQuantum"] ?? 0;
    
    $processDetails = [];
    for ($i = 0; $i < $numProcesses; $i++) {
        $processDetails[] = [
            'arrivalTime' => $_POST["arrivalTime{$i}"],
            'burstTime' => $_POST["burstTime{$i}"],
            'priority' => $_POST["priority{$i}"] ?? 0
        ];
    }
    
    // Define the paths to input.txt and output.txt in the php/ directory
    $inputFile = __DIR__ . '/input.txt';
    $outputFile = __DIR__ . '/output.txt';

    // Prepare the input file for the C++ program
    $fileContent = "$algorithm\n";
    $fileContent = "$numProcesses\n";
    foreach ($processDetails as $details) {
        $fileContent .= "{$details['arrivalTime']} {$details['burstTime']} {$details['priority']}\n";
    }
    if ($algorithm == 6 || $algorithm == 8) {
        $fileContent .= "$timeQuantum\n";
    }
    file_put_contents($inputFile, $fileContent);

    // Call the C++ program with the correct paths
    $command = escapeshellcmd("../cpp/scheduling $inputFile $outputFile");
    shell_exec($command);

    // Check if the output file was created
    if (file_exists($outputFile)) {
        // Read the output file
        $result = file_get_contents($outputFile);
        echo nl2br($result);
    } else {
        // Print error message if the output file was not created
        echo "Error: Output file was not created. Please check your C++ program.";
    }
}
?>
