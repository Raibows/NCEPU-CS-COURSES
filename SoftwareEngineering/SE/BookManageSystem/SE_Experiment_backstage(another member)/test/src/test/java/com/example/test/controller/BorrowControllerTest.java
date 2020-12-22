package com.example.test.controller;

import com.alibaba.fastjson.JSONObject;
import com.example.test.bean.BorrowInfo;
import lombok.extern.slf4j.Slf4j;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

/** 
* BorrowController Tester. 
* 
* @author <Authors name> 
* @since <pre>6ÔÂ 28, 2020</pre> 
* @version 1.0 
*/ 
@Slf4j
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class BorrowControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: show() 
* 
*/ 
@Test
public void testShow() throws Exception { 
//TODO: Test goes here... 
} 

/** 
* 
* Method: getBorrowInfoByID(@RequestBody(required = true) JSONObject jsonObject) 
* 
*/ 
@Test
public void testGetBorrowInfoByID() throws Exception { 
//TODO: Test goes here...
    String json = "{\"stuid\":\"201709000616\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    BorrowInfo borrowInfo = new BorrowInfo();
    borrowInfo.setStuid("201709000616");
    JSONObject jsonObject = new JSONObject();
    jsonObject = JSONObject.parseObject(JSONObject.toJSONString(borrowInfo));
    mvc.perform(MockMvcRequestBuilders.post("/search_borrow")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: getUnreturnInfoByID(@RequestBody(required = true) JSONObject jsonObject) 
* 
*/ 
@Test
public void testGetUnreturnInfoByID() throws Exception { 
//TODO: Test goes here...
    String json = "{\"stuid\":\"201709000616\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    BorrowInfo borrowInfo = new BorrowInfo();
    borrowInfo.setStuid("201709000616");
    JSONObject jsonObject = new JSONObject();
    jsonObject = JSONObject.parseObject(JSONObject.toJSONString(borrowInfo));
    mvc.perform(MockMvcRequestBuilders.post("/search_unreturn")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: borrowABook(@RequestBody(required = true) BorrowInfo borrowInfo) 
* 
*/ 
@Test
public void testBorrowABook() throws Exception { 
//TODO: Test goes here...
    String json = "{\"stuid\":\"201709000616\",\"isbn\":\"9780521880688\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    BorrowInfo borrowInfo = new BorrowInfo();
    borrowInfo.setStuid("201709000616");
    JSONObject jsonObject = new JSONObject();
    jsonObject = JSONObject.parseObject(JSONObject.toJSONString(borrowInfo));
    mvc.perform(MockMvcRequestBuilders.post("/borrow_book")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: returnABook(@RequestBody(required = true) BorrowInfo borrowInfo) 
* 
*/ 
@Test
public void testReturnABook() throws Exception { 
//TODO: Test goes here...
    String json = "{\"stuid\":\"201709000616\",\"isbn\":\"9780521880688\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    BorrowInfo borrowInfo = new BorrowInfo();
    borrowInfo.setStuid("201709000616");
    JSONObject jsonObject = new JSONObject();
    jsonObject = JSONObject.parseObject(JSONObject.toJSONString(borrowInfo));
    mvc.perform(MockMvcRequestBuilders.post("/return_book")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
