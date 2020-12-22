import request from "@/utils/request";

export function addComment(data) {
  return request({
    url:  '/search/addComment',
    method: 'post',
    data
  })
}

export function queryAllComment(data) {
  return request({
    url: '/search/queryAllComment',
    method: 'post',
    data
  })
}
