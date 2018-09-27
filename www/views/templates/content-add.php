<main role="main" class="container">
    <div class="row mt-5">
    <form method="POST" action="/post/create/send/" enctype="multipart/form-data" id="upload-form">
        <img alt="" style="width:400px;height:400px;" id="previewPh" src="/img/img-placeholder.svg"><br>
        <input type="file" id="file-selection" class="custom-file-input2" name="photo" onchange="previewPhFunc(this);" required><br><br>
        <input type="submit" id="bigassbutton" name="submit" value="Upload" style="margin-top:-10px;margin-bottom: 60px;">
    </form>
    </div>
</main>
           
<script>

function previewAvFunc(image) {
    if (image.files && image.files[0]) {
        var view = new FileReader();
        view.onload = function(e) {

            document.getElementById('previewAv').src = e.target.result;
        };
        view.readAsDataURL(image.files[0]);
    }
}
function previewPhFunc(image) {
    if (image.files && image.files[0]) {
        var view = new FileReader();
        view.onload = function(e) {
            document.getElementById('previewPh').src = e.target.result;
        };
        view.readAsDataURL(image.files[0]);
    }
}
</script>