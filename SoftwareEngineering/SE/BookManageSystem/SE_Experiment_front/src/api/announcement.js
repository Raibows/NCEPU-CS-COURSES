import request from "@/utils/request";

export function queryAllAnn(data) {
  return request({
    url: '/search/queryAllAnn',
    method: 'post',
    data
  })
}
export function addAnn(data) {
  return request({
    url: '/search/addAnn',
    method: 'post',
    data
  })
}
export function deleteAnn(data) {
  return request({
    url: '/search/deleteAnn',
    method: 'post',
    data
  })
}
export function updateAnn(data) {
  return request({
    url: '/search/updateAnn',
    method: 'post',
    data
  })
}
