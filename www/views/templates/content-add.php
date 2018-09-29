<main role="main" class="container">
    <div class="row mt-5">
        <div class="row container">
        <a href="/post/create/live/" class="btn btn-primary m-2"><i class="fa fa-camera"></i> Live</a>
        <a href="/post/create/add/" class="btn btn-primary m-2"><i class="fa fa-upload"></i> Upload</a>
        </div>
    <form method="POST" action="/post/create/send/" enctype="multipart/form-data" id="upload-form">
        <img alt="" style="width:350px;height:350px;" id="previewPh" src="/img/img-placeholder.svg"><br>
        <label for="comment">Caption:</label>
        <textarea class="form-control" rows="5" name ='caption' placeholder="My Amazing Shot!"></textarea>
        <input type="file" id="file-selection" class="btn-file mt-2" name="photo" onchange="previewPhFunc(this);" required><br><br>
        <input type="submit" name="submit" value="Upload" class="btn btn-warning">
    </form>
    </div>
</main>
           
<script>

var _validFileExtensions = [".jpg", ".jpeg", ".bmp", ".gif", ".png"];    

function previewAvFunc(image) {
    if (image.files && image.files[0]) {
        var view = new FileReader();
        view.onload = function(e) {

            document.getElementById('previewAv').src = e.target.result;
        };
        view.readAsDataURL(image.files[0]);
    }
}
function previewPhFunc(oInput) {
    
        if (oInput.type == "file") {
            var sFileName = oInput.value;
             if (sFileName.length > 0) {
                var blnValid = false;
                for (var j = 0; j < _validFileExtensions.length; j++) {
                    var sCurExtension = _validFileExtensions[j];
                    if (sFileName.substr(sFileName.length - sCurExtension.length, sCurExtension.length).toLowerCase() == sCurExtension.toLowerCase()) {
                        blnValid = true;
                        break;
                    }
                }
                 
                if (!blnValid) {
                    alert("Sorry, " + sFileName + " is invalid, allowed extensions are: " + _validFileExtensions.join(", "));
                    oInput.value = "";
                    return false;
                }
            }
            if (oInput.files && oInput.files[0]) {
                var view = new FileReader();
                view.onload = function(e) {
                    document.getElementById('previewPh').src = e.target.result;
                };
                view.readAsDataURL(oInput.files[0]);
            }
        }
        return true;
}


</script>