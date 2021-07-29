// Like
const	newlike = new XMLHttpRequest();
var		likes = [...document.querySelectorAll(".likes")];
var		likesCount = [...document.querySelectorAll(".likes-count")];
var		tempindex;

function likeIt(post, index) {
	post.onclick = function() {
		var		data = new FormData();
		tempindex = index;
		data.append("post", post.getAttribute('name'));
		newlike.open("POST", '/action/like/add/');
		newlike.send(data);
	}
	
}

if (likes)
{
	newlike.onreadystatechange = function() {
		likesCount[tempindex].innerHTML = this.responseText;
	};
	likes.forEach(likeIt);
}

// Comment
const	newcomment = new XMLHttpRequest();
var		commentCount = [...document.querySelectorAll(".comment-count")];
var		textComment = document.querySelector("#comment");
var		commentBtn = document.querySelector("#sendbtn");
var		anewComment = document.querySelector("#newcomment");

if (newcomment && commentBtn)
{
	function insertAfter(referenceNode, newNode) {
	    referenceNode.parentNode.insertBefore(newNode, referenceNode.nextSibling);
	}
	
	commentBtn.onclick = function() {
		var info = new FormData;
		if (textComment.value.length > 0) {
			info.append("post", textComment.value);
			info.append("fix", likes[0].getAttribute('name'));
			likesCount[0].innerHTML = likesCount[0].innerHTML;
			newcomment.open("POST", '/action/comment/add/');
			newcomment.send(info);
			newcomment.onreadystatechange = function() {
				if (this.readyState == 4) {
					if (this.status == 200) {
						let div = window.top.document.createElement('div');
						div.className = "comment-wrap";
						div.innerHTML = this.responseText;
						insertAfter(anewComment, div);
						commentCount[0].lastChild.nodeValue.innerHTML = commentCount[0].lastChild.nodeValue++;
						textComment.value = '';
					}
				}
			}
		};
	}
}

