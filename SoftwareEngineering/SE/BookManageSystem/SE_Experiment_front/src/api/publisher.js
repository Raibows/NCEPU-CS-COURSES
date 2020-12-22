import request from "@/utils/request";

export function getPublisherList(data) {
  return request({
    url: '/maintain/queryPubIdAndName',
    method: 'post',
    data
  })
}

export function queryAllPublisher(data) {
  return request({
    url: '/maintain/queryAllPublisher',
    method: 'post',
    data
  })
}

export function updatePublisher(data) {
  return request({
    url: '/maintain/updatePublisher',
    method: 'post',
    data
  })
}

export function addPublisher(data) {
  return request({
    url: '/maintain/addPublisher',
    method: 'post',
    data
  })
}

export function deletePublisher(data) {
  return request({
    url: '/maintain/deletePublisher',
    method: 'post',
    data
  })
}
