<template>
  <el-row :gutter="20">
    <el-col :span="11" style="margin: 20px">
      <el-form ref="form" :model="form" label-width="100 px">
        <el-form-item label="通知标题">
          <el-input v-model="form.name"></el-input>
        </el-form-item>
        <el-form-item label="通知类型">
          <el-select v-model="form.type" placeholder="请选择通知类型">
            <el-option label="公告" value="shanghai"></el-option>
            <el-option label="提醒" value="notice"></el-option>
          </el-select>
        </el-form-item>
        <el-form-item label="通知时间段">
          <el-date-picker
            v-model="form.date_range"
            type="daterange"
            range-separator="至"
            start-placeholder="开始日期"
            end-placeholder="结束日期">
          </el-date-picker>
        </el-form-item>
        <el-form-item label="通知正文">
          <el-input type="textarea" v-model="form.content"></el-input>
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="onSubmit">立即创建</el-button>
          <el-button>取消</el-button>
        </el-form-item>
      </el-form>
    </el-col>
    <el-col :span="11" style="margin: 20px">
      <el-table
        :data="tableData"
        style="width: 100%">
        <el-table-column
          label="通知期间"
          width="300">
          <template slot-scope="scope">
            <i class="el-icon-time"></i>
            <span style="margin-left: 10px">{{ scope.row.date }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="标题"
          width="340">
          <template slot-scope="scope">
            <el-popover trigger="hover" placement="top">
              <p>姓名: {{ scope.row.name }}</p>
              <p>住址: {{ scope.row.address }}</p>
              <div slot="reference" class="name-wrapper">
                <el-tag size="medium">{{ scope.row.name }}</el-tag>
              </div>
            </el-popover>
          </template>
        </el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button
              size="mini"
              type="success"
              @click="handleDelete(scope.$index, scope.row)">填入</el-button>
          </template>
        </el-table-column>
      </el-table>
    </el-col>
  </el-row>
</template>

<script>
export default {
name: "admin"
}
</script>

<style scoped>

</style>
