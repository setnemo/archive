<main role="main" class="container">
    <div class="row mt-5">






<?php if (isset($_SESSION['login'])) {
    ?>
        <div class="col-lg-6 col-md-6 col-sm-12 col-xs-12">
        <a href="/post/create/live/" class="btn btn-primary m-3"><i class="fa fa-camera"></i> Live</a>
        <a href="/post/create/add/" class="btn btn-primary m-3"><i class="fa fa-upload"></i> Upload</a>
            <div class="vidprevabs" style="position: relative;">
                    <video class="previewVid col-12" id="previewVid"></video>
                    <img alt="" class="ph vidprevabs cropprev col-12" src="">
                    <img alt="" class="pr vidprevabs cropprev col-12" src="">
                    <canvas style="display: none;" class='vidprevabs'></canvas>
                    <div class="row ml-2">
                    <button value="Snap" class="btn btn-success p-auto mt-2 ml-2 mb-2" onclick="snapQ();"><i class="fa fa-camera"></i></button>
                    <button value="Snap" class="btn btn-danger p-auto mt-2 ml-2 mb-2" onclick="delsnapQ();"><i class="fa fa-trash"></i></button>
                        
                    </div>
                <form method="POST" action="/post/create/send-live/" enctype="multipart/form-data" id="upload-form">

                    <input id="snapupload" type="text" name="photo" style="display: none;" required>
                    <label class="gender" style="display: none;">Female</label>
                    <input type="radio" name="gender" class="gender mt-2 ml-2 mb-2" id="fr1" onclick="clickBorder(this)"  style="display: none;"  value="female">
                    <label class="gender" style="display: none;">Male</label>
                    <input type="radio" name="gender" class="gender mt-2 ml-2 mb-2" id="fr2" onclick="clickBorder(this)"  style="display: none;"  value="male">
                    <label class="gender" style="display: none;">Other</label>
                    <input type="radio" name="gender" class="gender mt-2 ml-2 mb-2" id="fr3" onclick="clickBorder(this)"  style="display: none;"  value="other">
                    <label class="gender" style="display: none;">Off</labrl>
                        <input type="radio" name="gender" class="gender mt-2 ml-2 mb-2" id="fr4" onclick="clickBorder(this)"  style="display: none;"  value="off">
                    <label for="comment">Caption:</label>
                    <textarea class="form-control" rows="5" name ='caption' placeholder="My Amazing Shot!"></textarea>
                    <input type="submit" class="btn btn-warning mt-2" name="submit" value="Upload">
                </form>
            </div>
        </div>
    <script>
        function clickBorder(i) {
            document.getElementsByClassName('pr')[0].src = '/img/overlays/'+ i.id + '.png';
        }
    </script>

    <?php
}
?>









    </div>
</main>
           
<script>
    function radioBtnIt(radioBtn, index) {
        radioBtn.style.display = 'block';
    }

function snapQ() {
    var draft = document.querySelector('canvas'),
        input = document.querySelector('video.previewVid'),
        img = document.querySelector('img.ph'),

        w = 640,
        h = 480,
        c = draft.getContext('2d');

var     radioBtn = [...document.querySelectorAll(".gender")];

    draft.width = 480;
    draft.height = h;
    c.drawImage(input, -80, 0, w, h);
    var idataURL = draft.toDataURL('image/png');
    img.setAttribute('src', idataURL);
    document.getElementById('snapupload').setAttribute('value', idataURL);
    input.style.display = 'none';
    img.style.opacity = '0';
    radioBtn.forEach(radioBtnIt);
    setTimeout(function() {
        img.style.opacity = '1';
    }, 500);
}
function delsnapQ() {
    var img = document.querySelector('img.ph');
    img.setAttribute('src', "");
    document.querySelector('video.previewVid').style.display = 'block';

}

window.addEventListener("load", function() {
    const video = document.getElementById('previewVid');
    var s = {audio: false, video: true};
   
    function success(input) {
        video.srcObject = input;
        video.play();
    }

    function fail() {
        alert("Ooops, something's gone wrong...");
    }

    if (navigator.getUserMedia) {
        navigator.getUserMedia(s, success, fail);
    }
}, false);

</script>