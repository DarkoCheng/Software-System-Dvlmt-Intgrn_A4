<!DOCTYPE html>
<html>
<head>
<style>
/* The Modal (background) */
.modal {
    display: none; /* Hidden by default */
    position: fixed; /* Stay in place */
    z-index: 1; /* Sit on top */
    padding-top: 100px; /* Location of the box */
    left: 0;
    top: 0;
    width: 100%; /* Full width */
    height: 100%; /* Full height */
    overflow: auto; /* Enable scroll if needed */
    background-color: rgb(0,0,0); /* Fallback color */
    background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
}

/* Modal Content */
.modal-content {
    position: relative;
    background-color: #fefefe;
    margin: auto;
    padding: 0;
    border: 1px solid #888;
    width: 80%;
    box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19);
    -webkit-animation-name: animatetop;
    -webkit-animation-duration: 0.4s;
    animation-name: animatetop;
    animation-duration: 0.4s
}

/* Add Animation */
@-webkit-keyframes animatetop {
    from {top:-300px; opacity:0} 
    to {top:0; opacity:1}
}
 
@keyframes animatetop {
    from {top:-300px; opacity:0}
    to {top:0; opacity:1}
}

/* The Close Button */
.close {
    color: white;
    float: right;
    font-size: 28px;
    font-weight: bold;
}

.close:hover,
.close:focus {
    color: #000;
    text-decoration: none;
    cursor: pointer;
}

.modal-header {
    padding: 2px 16px;
    background-color: #5cb85c;
    color: white;
}

.modal-body {padding: 2px 16px;}

.modal-footer {
    padding: 2px 16px;
    background-color: #5cb85c;
    color: white;
}

form {
    display: inline;

}
</style>
</head>
<body>

<!-- Trigger/Open The Modal -->
<button id="myBtn">convert</button>

<!-- The Modal -->
<div id="myModal" class="modal">

  <!-- Modal content -->
  <div class="modal-content">
    <div class="modal-header">
      <span class="close">×</span>
      <h2>Modal Header</h2>
    </div>
    <div class="modal-body">
     <?php
        $files = "files/";
                echo ("<br>");

        // Open a directory, and read its contents
                if (is_dir($files))
                {
                        if ($dh1 = opendir($files))
                                                {
                        while (($file1 = readdir($dh1)) !== false)
                        {
                                $array1[] = $file1;
                        }
                        closedir($dh1);
                        }
                }
    ?>
    <form action="" method="post">
                <select name="mySelect" size = "<?php echo count($array1) ?>">
                 <?php foreach($array1 as $value1):?>
                     <?php if (strpos($value1, ".txt") == true &&strpos($value1, ".info") == false)
                                {
                                        if (strpos($value1, ".html") == false)
                                        {
                                        ?>
                                                <option value="<?php echo $value1?>"><?php echo $value1?></option>
                                        <?php }
                                }
                        ?>
                        <?php endforeach;?>
                </select>
                <input type="submit" name="submit" value="ok" class="ok"/>
        </form>
    </div>
    <div class="modal-footer">
      <button class="close1">cancel</button>
      <h3></h3>
    </div>
  </div>

</div>

 <form>
        </form>
        <form action="" method="post" enctype="multipart/form-data">
        <input type="file" name="file" id="file" onChange="this.form.submit();">
        </form> 

<!-- Trigger/Open The Modal -->
<button id="myBtn1">DB Store</button>

<!-- The Modal -->
<div id="myModal1" class="modal">

  <!-- Modal content -->
  <div class="modal-content">
    <div class="modal-header">
      <span class="close111">×</span>
      <h2>Modal Header1</h2>
    </div>
    <div class="modal-body">
     <?php
        $files1 = "files/";
                echo ("<br>");

        // Open a directory, and read its contents
                if (is_dir($files1))
                {
                        if ($dh11 = opendir($files1))
                                                {
                        while (($file11 = readdir($dh11)) !== false)
                        {
                                $array11[] = $file11;
                        }
                        closedir($dh11);
                        }
                }
    ?>
    <form action="" method="post">
                <select name="myDb" size = "<?php echo count($array11) ?>">
                 <?php foreach($array11 as $value11):?>
                     <?php if (strpos($value11, ".txt") == true &&strpos($value11, ".info") == false)
                                {
                                        if (strpos($value11, ".html") == false)
                                        {
                                        ?>
                                                <option value="<?php echo $value11?>"><?php echo $value11?></option>
                                        <?php }
                                }
                        ?>
                        <?php endforeach;?>
                </select>
                <input type="submit" name="submit1" value="ok" class="ok1"/>
        </form>
    </div>
    <div class="modal-footer">
      <button class="close11">cancel</button>
      <h3></h3>
    </div>
  </div>

</div>

<?php
if(isset($_POST['submit']))
{
        $selected_val = $_POST['mySelect'];  // Storing Selected Value In Variable
        $file22 = "files/". $selected_val;
        echo "should be wrong $file22";
        shell_exec("./A4 $file22 0");
        //shell_exec("./test $files22");
        //echo "<meta http-equiv='refresh' content='0'>";
}
else if (isset($_POST['submit1']))
{
    $selected_val1 = $_POST['myDb'];  // Storing Selected Value In Variable
    $file12 = "files/". $selected_val1;
    echo "     the option is $file12";
    shell_exec("./A4 $file12 1");
    //echo "<meta http-equiv='refresh' content='0'>";
}
?>

<?php
$dir = "files/";
echo ("<br>");
// Open a directory, and read its contents
if (is_dir($dir))
{
    if ($dh = opendir($dir))
    {
        while (($file = readdir($dh)) !== false)
        {
            $array[] = $file;
        }
        closedir($dh);
        foreach($array as $value)
        {
            if (strpos($value, ".txt") == true || strpos($value, ".html") == true)
            {
                if (strpos($value, ".info") == false)
                {
                    if (strpos($value, ".txt.html") == true)
                    {
                        $array2[] = $value;
                    }
                    elseif(strpos($value, ".txt") == true)
                    {
                        $array21[] = $value;
                    }
                }
            }
        }

    }
}
$string = shell_exec("./db -select");
//echo "$string<br>";
$parse = explode(" ", $string);
$i = count($parse);
$j = 0;
foreach ($parse as $parse1)
{
    $j = $j + 1;
    if ($j == $i)
    {
        break;
    }
    else if ($parse1 == "fail" || $parse1 == "select" || $parse1 == "drop")
    {
        continue;
    }
    else
    {
        $array2[] = $parse1.".txt.html";
    }
}
sort($array2);
echo "html files:<br>";
foreach ($array2 as $value2)
{
    $string3 = explode(".txt.html", $value2);
    //echo "string3: $string3[0]<br>";
    if (strpos($string, $string3[0]) === false)
    {
        //$string1 = shell_exec("./db -data "explode(".txt.html", $value2)"");
        echo "<a href=files/$value2>$value2</a><br>";
    }
    else
    {
        //echo "$string3";
        $string4 = shell_exec("./db -data $string3[0]");
        //echo $string4;
        ?>
        <input type="button" onclick="myFunction1()" value="<?php echo "$value2"?>">
        <?php
        echo '<br>';
        echo "<script>myfunction1()</script>";
        //echo "<a target="_blank">$value2</a><br>";
        //echo "second<br>";
    }
}
echo "<br><br>";
echo "txt files:<br>";
foreach ($array21 as $value21)
{
    echo "<a href=files/$value21>$value21</a><br>";
}
if ($_FILES["file"]["error"] > 0)
{
    //echo "Return Code: " . $_FILES["file"]["error"] . "<br />";
}
else
{
    //echo "Upload: " . $_FILES["file"]["name"] . "<br />";
    //echo "Type: " . $_FILES["file"]["type"] . "<br />";
    //echo "Size: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
    //echo "Temp file: " . $_FILES["file"]["tmp_name"] . "<br />";

    if (file_exists("files/" . $_FILES["file"]["name"]))
    {
        //echo $_FILES["file"]["name"] . " already exists. ";
    }
    else
    {

        if (move_uploaded_file($_FILES["file"]['tmp_name'],
            "files/" . $_FILES["file"]["name"]))
        {
            //echo "Stored in: " . "files/" . $_FILES["file"]["name"];
            echo "<meta http-equiv='refresh' content='0'>";
        }
        else
        {
                //echo $_FILES['file']['error'];
        }
    }
}
?>


<script>
// Get the modal
var modal = document.getElementById('myModal');

// Get the button that opens the modal
var btn = document.getElementById("myBtn");

// Get the <span> element that closes the modal
var span = document.getElementsByClassName("close")[0];
var span1 = document.getElementsByClassName("close1")[0];
var ok = document.getElementsByClassName("ok")[0];
// When the user clicks the button, open the modal 
btn.onclick = function()
{
    modal.style.display = "block";
}

// When the user clicks on <span> (x), close the modal
span.onclick = function()
{
    modal.style.display = "none";
}
span1.onclick = function()
{
    modal.style.display = "none";
}
ok.onclick = function()
{
        modal.style.display = "none";
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event)
{
    if (event.target == modal)
    {
        modal.style.display = "none";
    }
}
</script>

<script>
// Get the modal
var modal1 = document.getElementById('myModal1');

// Get the button that opens the modal
var btn1 = document.getElementById("myBtn1");

// Get the <span> element that closes the modal
var span111 = document.getElementsByClassName("close111")[0];
var span11 = document.getElementsByClassName("close11")[0];
var ok1 = document.getElementsByClassName("ok1")[0];
// When the user clicks the button, open the modal 
btn1.onclick = function()
{
    modal1.style.display = "block";
}

// When the user clicks on <span> (x), close the modal
span1.onclick = function()
{
    modal1.style.display = "none";
}
span111.onclick = function()
{
    modal1.style.display = "none";
}
ok1.onclick = function()
{
        modal1.style.display = "none";
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event)
{
    if (event.target == modal1)
    {
        modal1.style.display = "none";
    }
}
</script>

<script>
function myFunction1()
{
    var el = document.createElement( 'html' );

    var myvar = <?php echo json_encode($string4); ?>;
    el.innerHTML = myvar;
    //window.alert(document.write(el.innerHTML)); // this is the message in ""
   // document.write("<p>Strike: " + txt.strike() + "</p>");
   document.write(el.innerHTML)
}
</script>



</body>
</html> 


