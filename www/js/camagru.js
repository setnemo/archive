const	xhr5 = new XMLHttpRequest();
var		likes = [...document.querySelectorAll(".likes")];
var		likesCount = [...document.querySelectorAll(".likes-count")];
var		tempindex;

function likeIt(post, index) {
	post.onclick = function() {
		var		data = new FormData();

		tempindex = index;
		data.append("post", post.getAttribute('name'));
		xhr5.open("POST", '/action/like/add/');
		xhr5.send(data);
	}
	
}

if (likes)
{
	xhr5.onreadystatechange = function() {

		likesCount[tempindex].innerHTML = this.responseText;
	};

	likes.forEach(likeIt);
}