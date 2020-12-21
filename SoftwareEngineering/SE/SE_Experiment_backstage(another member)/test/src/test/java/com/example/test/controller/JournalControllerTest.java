package com.example.test.controller;

import com.example.test.bean.JournalBean;
import com.example.test.bean.JournalSubscribeInfo;
import lombok.extern.slf4j.Slf4j;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After;
import org.junit.runner.RunWith;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import com.alibaba.fastjson.JSONObject;
import com.example.test.ResultVO;
import com.example.test.bean.BorrowInfo;
import com.example.test.service.BorrowInfoService;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Controller;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;

/** 
* JournalController Tester. 
* 
* @author <Authors name> 
* @since <pre>6月 28, 2020</pre> 
* @version 1.0 
*/ 
@Slf4j
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class JournalControllerTest {
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
* Method: getJournalInfo(@RequestBody(required = true)JSONObject jsonObject) 
* 
*/ 
@Test
public void testGetJournalInfo() throws Exception { 
//TODO: Test goes here...
    String json = "{\"period\":\"年刊\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    mvc.perform(MockMvcRequestBuilders.post("/search_journal")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addJournal(@RequestBody(required = true) JournalBean journalBean) 
* 
*/ 
@Test
public void testAddJournal() throws Exception { 
//TODO: Test goes here...
    JournalBean journalBean = new JournalBean();
    journalBean.setNo("1524-7894");
    journalBean.setDescription("好的期刊！");
    journalBean.setJournalName("好期刊");
    journalBean.setPeriod("月刊");
    journalBean.setStartYear("2018");
    String json = JSONObject.toJSONString(journalBean);
    mvc.perform(MockMvcRequestBuilders.post("/add_journal")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteJournal(@RequestBody(required = true) JournalBean journalBean) 
* 
*/ 
@Test
public void testDeleteJournal() throws Exception { 
//TODO: Test goes here...
    JournalBean journalBean = new JournalBean();
    journalBean.setNo("1524-7894");
    String json = JSONObject.toJSONString(journalBean);
    mvc.perform(MockMvcRequestBuilders.post("/delete_journal")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: modifyJournalDescription(@RequestBody(required = true) JournalBean journalBean) 
* 
*/ 
@Test
public void testModifyJournalDescription() throws Exception { 
//TODO: Test goes here...
    JournalBean journalBean = new JournalBean();
    journalBean.setNo("1524-7894");
    journalBean.setDescription("好的期刊！");
    journalBean.setPeriod("月刊");
    String json = JSONObject.toJSONString(journalBean);
    mvc.perform(MockMvcRequestBuilders.post("/modify_journal")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: subscribeJournal(@RequestBody(required = true)JournalSubscribeInfo journalSubscribeInfo) 
* 
*/ 
@Test
public void testSubscribeJournal() throws Exception { 
//TODO: Test goes here...
    JournalSubscribeInfo journalSubscribeInfo = new JournalSubscribeInfo();
    journalSubscribeInfo.setStuId("201709000602");
    journalSubscribeInfo.setJournalName("好期刊");
    journalSubscribeInfo.setJournalNo("1544-1936");
    journalSubscribeInfo.setPeriod("年刊");
    journalSubscribeInfo.setDescription("真好！");
    String json = JSONObject.toJSONString(journalSubscribeInfo);
    mvc.perform(MockMvcRequestBuilders.post("/modify_journal")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: cancelSubscribe(@RequestBody(required = true) JSONObject jsonObject) 
* 
*/ 
@Test
public void testCancelSubscribe() throws Exception { 
//TODO: Test goes here...
    String json = "{\"journalNo\":\"1544-1932\",\"stuId\":\"201709000616\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    mvc.perform(MockMvcRequestBuilders.post("/cancel_subscribe")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: searchSubscribe(@RequestBody(required = true) JSONObject jsonObject) 
* 
*/ 
@Test
public void testSearchSubscribe() throws Exception { 
//TODO: Test goes here...
    String json = "{\"stuId\":\"201709000616\",\"pageNum\":\"1\",\"pageSize\":\"5\"}";
    mvc.perform(MockMvcRequestBuilders.post("/search_subscribe")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
