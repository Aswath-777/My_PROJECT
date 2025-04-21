<!DOCTYPE html>
<html>
<head>
    <title>Employee Form</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            padding: 20px;
        }
        .form-container {
            background-color: white;
            padding: 30px;
            border-radius: 10px;
            max-width: 500px;
            margin: auto;
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        input, select {
            width: 100%;
            padding: 10px;
            margin: 8px 0;
            border: 1px solid #ccc;
            border-radius: 5px;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px;
            border: none;
            border-radius: 5px;
            width: 100%;
        }
        .success {
            color: green;
            margin-top: 10px;
        }
    </style>
</head>
<body>

<div class="form-container">
    <h2>Employee Registration</h2>
    <form method="post" action="">
        <label>ID:</label>
        <input type="TEXT" name="id" required>

        <label>Name:</label>
        <input type="text" name="name" required>

        <label>Email:</label>
        <input type="email" name="email" required>

        <label>Department:</label>
        <input type="text" name="department" required>

        <label>Joining Date:</label>
        <input type="date" name="joining_date" required>

        <button type="submit" name="submit">Submit</button>
    </form>

    <?php
    if (isset($_POST['submit'])) {
       
        $conn = new mysqli("localhost", "root", "", "company");

        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }

        
        $id = $_POST['id'];
        $name = $_POST['name'];
        $email = $_POST['email'];
        $department = $_POST['department'];
        $joining_date = $_POST['joining_date'];

        
        $sql = "INSERT INTO employees (id, name, email, department, joining_date)
                VALUES ('$id', '$name', '$email', '$department', '$joining_date')";

        if ($conn->query($sql) === TRUE) {
            header("Location: success.php");
            exit();
            
        } else {
            echo "<p style='color:red;'>Error: " . $conn->error . "</p>";
        }

        
        $conn->close();
    }
    ?>
</div>

</body>
</html>
