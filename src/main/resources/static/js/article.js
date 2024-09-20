/* 삭제 버튼 구현 */
const deleteButton = document.getElementById('delete-btn');

if (deleteButton){
    deleteButton.addEventListener('click', event => {
        let id = document.getElementById('article-id').value;
        fetch(`/api/articles/${id}`, {method: 'DELETE'})
            //DELETE 요청을 fetch하기 때문에 진짜로 웹 상에서 게시글이 삭제됨
            .then(() => {
                alert('삭제가 완료되었습니다.');
                location.replace('/articles');
            });
        //article-id, delete-btn 모두 html에 id값으로 설정
    });
}
/* 수정, 생성 버튼 구현 */
const modifyButton = document.getElementById('modify-btn');

if (modifyButton){
    modifyButton.addEventListener('click', event => {
        let params = new URLSearchParams(location.search);
        let id = params.get('id');

        fetch(`/api/articles/${id}`, {
            method: 'PUT',
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                title: document.getElementById('title').value,
                content: document.getElementById('content').value
            })
        })//PUT 요청을 fetch,
            .then(() => {
                alert('수정이 완료되었습니다.');
                location.replace('/articles');
            });
    });
}

const createButton = document.getElementById('create-btn');

if (createButton){
    createButton.addEventListener('click', event => {
        fetch("/api/articles", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                title: document.getElementById("title").value,
                content: document.getElementById("content").value
            })
        })//PUT 요청을 fetch,
            .then(() => {
                alert('등록이 완료되었습니다.');
                location.replace("/articles");
            });
    });
}